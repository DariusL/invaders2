#include "includes.h"
#include "SomethingConcurent.h"

volatile bool SomethingConcurent::doWork = true;

SomethingConcurent::SomethingConcurent(int objectCount, float radius, int threadCount)
:instancer(objectCount, radius, threadCount)
{
	for (int i = 0; i < threadCount; i++)
		workers.emplace_back(&SomethingConcurent::Worker, ref(instancer), objectCount);
}


SomethingConcurent::~SomethingConcurent()
{
	doWork = false;
	for (auto &t : workers)
		t.join();
}

void SomethingConcurent::Worker(Instancer &instancer, int objectCount)
{
	bool valid;
	while (doWork)
	{
		float frame = instancer.FrameStart();
		if (frame >= 0.000001)
		{
			while (doWork)
			{
				auto &obj = instancer.GetPhysicsTask(valid);
				if (!valid)
					break;

				XMVECTOR subjectPos = XMLoadFloat3(&obj.pos);
				XMVECTOR acceleration = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				for (int i = 0; i < objectCount; i++)
				{
					auto &target = instancer.Get(i);
					XMVECTOR targetPos = XMLoadFloat3(&target.GetPos());
					acceleration += Acceleration(subjectPos, targetPos, target.GetMass());
				}
				XMVECTOR subjectSpeed = XMLoadFloat3(&obj.speed);
				XMVECTOR nextPos = subjectPos + frame * subjectSpeed + acceleration * (frame * frame * 0.5f);
				XMVECTOR speed = (nextPos - subjectPos) / frame;
				XMStoreFloat3(&obj.nextPos, nextPos);
				XMStoreFloat3(&obj.speed, speed);
			}
		}
	}
}

XMVECTOR XM_CALLCONV SomethingConcurent::Acceleration(XMVECTOR subject, XMVECTOR target, float targetMass)
{
	XMVECTOR temp = target - subject;
	float l;
	XMStoreFloat(&l, XMVector3Length(temp));
	if (l < 20.0f)
		return XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	return temp * (G * targetMass / pow(l, 3.0f));
}

void SomethingConcurent::OnLoop(float framelength)
{
	instancer.OnLoop(framelength);
}