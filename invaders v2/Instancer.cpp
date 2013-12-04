#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(size_t objectCount, float radius, int workerCount)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount),
workerCount(workerCount), atStart(0), blockStart(true), stop(false)
{
	//sugeneruojama n objektu issidesciusiu sferoje
	default_random_engine gen;
	uniform_real_distribution<float> dist(-10.0f, 10.0f);
	auto num = bind(dist, gen);
	instanceCount = objectCount;
	for (size_t i = 0; i < objectCount; i++)
	{
		XMVECTOR vec = XMVectorSet(num(), num(), num(), 0.0f);
		vec = XMVector3Normalize(vec) * radius;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vec);
		objects.emplace_back(pos);
	}
}

float Instancer::FrameStart()
{
	//darbiniu giju kvieciamas metodas naujo kadro pradzioje
	unique_lock<mutex> lock(mtx);
	int nr = atStart.fetch_add(1);
	//jei atejo paskutinis darbuotojas, pazadinama pagrindine gija
	if (nr == workerCount - 1)
		mainWaitCondition.notify_one();
	workerWaitCondition.wait(lock, [=]{return !blockStart || stop; });
	nr = atStart.fetch_sub(1);
	//isejus paskutiniam darbuotojui, pazadinama pagrindine gija
	if (nr == 1)
		mainWaitCondition.notify_one();
	return frame;
}

Entity &Instancer::GetPhysicsTask(bool &valid)
{
	//indeksas objekto kuri grazinsime apdoroti
	size_t ret = currentObject.fetch_add(1);
	if (ret < instanceCount)
	{
		valid = true;
	}
	else
	{
		//visi objektai jau aprodoti
		valid = false;
		ret = 0;
	}
	return objects[ret];
}

void Instancer::OnLoop(float framelength)
{
	frame = framelength * 10.0f;

	unique_lock<mutex> lock(mtx);
	//pagrindine gija laukia, kol darbines apskaiciavo fizika siam kadrui
	mainWaitCondition.wait(lock, [=]{return atStart == workerCount || stop; });

	//objektai perstatomi i naujas koordinates
	for (size_t i = 0; i < instanceCount; i++)
	{
		auto &obj = objects[i];
		obj.pos = obj.nextPos;
	}
		
	blockStart = false;
	currentObject = 0;
	workerWaitCondition.notify_all();
	mainWaitCondition.wait(lock, [=]{return atStart == 0 || stop; });
	blockStart = true;
	//palaukiame kol visi darbininkai iseis is FrameStart, nustatome blokavima kitam kadrui
}

bool Instancer::Update(ComPtr<ID3D11DeviceContext> context)
{
	//ikeliame objektu duomenis i gpu atvaizdavimui
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	XMFLOAT3 *data = (XMFLOAT3*)mappedResource.pData;

	for (size_t i = 0; i < instanceCount; i++)
		data[i] = objects[i].pos;

	context->Unmap(instanceBuffer.Get(), 0);

	return true;
}

void Instancer::Stop()
{
	//baigimo atveju zadinamos visos gijos
	stop = true;
	mainWaitCondition.notify_all();
	workerWaitCondition.notify_all();
}