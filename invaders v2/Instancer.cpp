#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(size_t objectCount, float radius, int workerCount)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount),
workerCount(workerCount), atStart(0), blockStart(true), stop(false)
{
	default_random_engine gen;
	uniform_real_distribution<float> dist(-10.0f, 10.0f);
	auto num = bind(dist, gen);
	instanceCount = objectCount;
	for (int i = 0; i < objectCount; i++)
	{
		XMVECTOR vec = XMVectorSet(num(), num(), num(), 0.0f);
		vec = XMVector3Normalize(vec) * radius;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vec);
		objects.emplace_back(pos);
	}
}

Instancer::~Instancer()
{
}


float Instancer::FrameStart()
{
	unique_lock<mutex> lock(mtx);
	int nr = atStart.fetch_add(1);
	if (nr == workerCount - 1)
		mainWaitCondition.notify_one();
	workerWaitCondition.wait(lock, [=]{return !blockStart || stop; });
	nr = atStart.fetch_sub(1);
	if (nr == 1)
		mainWaitCondition.notify_one();
	return frame;
}

Entity &Instancer::GetPhysicsTask(bool &valid)
{
	int ret = currentObject.fetch_add(1);
	if (ret < instanceCount)
	{
		valid = true;
	}
	else
	{
		valid = false;
		ret = 0;
	}
	return objects[ret];
}

void Instancer::OnLoop(float framelength)
{
	frame = framelength * 10.0f;

	unique_lock<mutex> lock(mtx);
	mainWaitCondition.wait(lock, [=]{return atStart == workerCount || stop; });

	for (int i = 0; i < instanceCount; i++)
	{
		auto &obj = objects[i];
		obj.pos = obj.nextPos;
	}
		
	blockStart = false;
	currentObject = 0;
	workerWaitCondition.notify_all();
	mainWaitCondition.wait(lock, [=]{return atStart == 0 || stop; });
	blockStart = true;
}

bool Instancer::Update(ComPtr<ID3D11DeviceContext> context)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	XMFLOAT3 *data = (XMFLOAT3*)mappedResource.pData;

	for (int i = 0; i < instanceCount; i++)
		data[i] = objects[i].pos;

	context->Unmap(instanceBuffer.Get(), 0);

	return true;
}

void Instancer::Stop()
{
	stop = true;
	mainWaitCondition.notify_all();
	workerWaitCondition.notify_all();
}