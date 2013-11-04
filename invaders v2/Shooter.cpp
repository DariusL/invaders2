#include "includes.h"
#include "Shooter.h"


Shooter::Shooter(float fireRate)
{
	this->fireRate = fireRate;
	this->lastFired = 0;
}


Shooter::~Shooter(void)
{
}

bool Shooter::Fire()
{
	float now = clock() / (float)CLOCKS_PER_SEC;
	lastFired = now;
	return true;
}