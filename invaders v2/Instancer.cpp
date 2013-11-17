#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(int objectCount, float radius, int workerCount)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount),
workerCount(workerCount), atStart(0), blockStart(true), superwake(false), first(true)
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
	superwake = true;
	mainWaitCondition.notify_all();
	workerWaitCondition.notify_all();
}


float Instancer::FrameStart()
{
	unique_lock<mutex> lock(mtx);
	int nr = atStart.fetch_add(1);
	if (nr == workerCount - 1)
		mainWaitCondition.notify_one();
	workerWaitCondition.wait(lock, [=]{return !blockStart || superwake; });
	nr = atStart.fetch_sub(1);
	if (nr == 1)
		mainWaitCondition.notify_one();
	return frame;
}

Entity &Instancer::GetPhysicsTask(bool &valid)
{
	int ret = currentObject.fetch_add(1);
	ret++;
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
	mainWaitCondition.wait(lock, [=]{return atStart == workerCount || superwake; });
	if (!first)
	{
		for (int i = 0; i < instanceCount; i++)
		{
			auto &obj = objects[i];
			instanceData[i] = obj.pos = obj.nextPos;
		}
	}
	first = false;
		
	blockStart = false;
	currentObject = 0;
	workerWaitCondition.notify_all();
	mainWaitCondition.wait(lock, [=]{return atStart == 0 || superwake; });
	blockStart = true;
}