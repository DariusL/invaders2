#include "includes.h"
#include "Shooter.h"


Shooter::Shooter(float fireRate, float speed)
{
	this->fireRate = fireRate;
	this->lastFired = 0;
	this->speed = speed;
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