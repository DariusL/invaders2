#include "includes.h"
#include "Gun.h"
#include "Observers.h"
#include "ResourceManager.h"

Gun::Gun(int spawnEvent, uint firePeriod, float off, ColorModel &model)
:spawnEvent(spawnEvent), firePeriod(firePeriod), lastFired(0), bulletSize(model.GetSize())
{
}

void Gun::Fire(e::XMVECTOR gunPos)
{
	uint now = clock();
	if (lastFired + firePeriod <= now)
	{
		lastFired = now;
		Observers::Notify(spawnEvent, e::make_shared<GameEntity>(gunPos + Utils::VectorSet(0.0f, off), 1, 10, 0.0f, bulletSize));
	}
}