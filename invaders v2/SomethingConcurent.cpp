#include "includes.h"
#include "SomethingConcurent.h"

SomethingConcurent::SomethingConcurent(size_t objectCount, float radius, int threadCount)
:instancer(objectCount, radius, threadCount), run(true)
{
	//paleidziamos visos darbines gijos
	for (int i = 0; i < threadCount; i++)
		workers.emplace_back(Worker, ref(instancer), objectCount, ref(run));
}


SomethingConcurent::~SomethingConcurent()
{
	run = false;
	instancer.Stop();
	for (auto &t : workers)
		t.join();
}

void SomethingConcurent::Worker(Instancer &instancer, size_t objectCount, bool &run)
{
	//vykdoma kol nera pabaigos salygos
	bool valid;
	while (run)
	{
		float frame = instancer.FrameStart();
		while (run)
		{
			auto &obj = instancer.GetPhysicsTask(valid);
			//jei visi objektai apdoroti, griztame i kadro pradzia ir sinchronizuojames su pagrindine gija
			if (!valid)
				break;

			//fizika
			XMVECTOR subjectPos = XMLoadFloat3(&obj.pos);
			XMVECTOR acceleration = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			for (size_t i = 0; i < objectCount; i++)
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

XMVECTOR XM_CALLCONV SomethingConcurent::Acceleration(XMVECTOR subject, XMVECTOR target, float targetMass)
{
	//daugiau fizikos
	XMVECTOR temp = target - subject;
	float l;
	XMStoreFloat(&l, XMVector3Length(temp));
	if (l < 5.0f)
		return XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	return temp * (targetMass / Utils::Pow<3>(l));
}

void SomethingConcurent::OnLoop(float framelength)
{
	instancer.OnLoop(framelength);
}