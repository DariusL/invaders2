#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(int objectCount, float radius, int workerCount)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount), workerCount(workerCount), passed(0), calculating(false)
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

bool Instancer::Update(ComPtr<ID3D11DeviceContext> context)
{
	unique_lock<mutex> lock(mtx);
	calculating = true;
	currentObject = 0;
	workerWaitCondition.notify_all();
	mainWaitCondition.wait(lock, [=]{return !calculating; });
	return BaseInstancer::Update(context);
}


void Instancer::FrameStart()
{
	unique_lock<mutex> lock(mtx);
	workerWaitCondition.wait(lock, [=]{return calculating; });
}

void Instancer::Barrier()
{
	unique_lock<mutex> lock(mtx);
	passed.fetch_add(1);
	barrierCondition.wait(lock, [=]{return workerCount == passed; });
	passed.store(0);
}

void Instancer::Done()
{
	Barrier();
	calculating = false;
	mainWaitCondition.notify_one();
}

Entity &Instancer::GetPhysicsTask(bool &valid)
{
	unique_lock<mutex> lock(mtx);
	distributeCondition.wait(lock, [=]{ return !distributingJobs; });
	distributingJobs = true;
	int ret = 0;
	if (currentObject < instanceCount)
	{
		ret = currentObject++;
		valid = true;
	}
	else
	{
		valid = false;
	}
	distributingJobs = false;
	distributeCondition.notify_one();
	return objects[ret];
}