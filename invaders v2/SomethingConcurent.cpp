#include "includes.h"
#include "SomethingConcurent.h"


SomethingConcurent::SomethingConcurent(int objectCount, float radius, int threadCount)
:instancer(objectCount, radius, threadCount)
{
	for (int i = 0; i < threadCount; i++)
		workers.emplace_back(&SomethingConcurent::Worker, ref(instancer), objectCount);
}


SomethingConcurent::~SomethingConcurent()
{
}

void SomethingConcurent::Worker(Instancer &instancer, int objectCount)
{
	while (true)
	{
		instancer.FrameStart();

		//fiziks

		instancer.Done();
	}
}