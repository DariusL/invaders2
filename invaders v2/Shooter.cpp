#include "includes.h"
#include "Shooter.h"


Shooter::Shooter(D3DXVECTOR2 size, float speed, float fireRate)
{
	this->size = size;
	this->speed = speed;
	this->fireRate = fireRate;
	this->lastFired = 0;
	this->dead = false;
}


Shooter::~Shooter(void)
{
}

bool Shooter::Fire()
{
	float now = clock() / (float)CLOCKS_PER_SEC;
	if(lastFired + fireRate > now || dead)
		return false;
	lastFired = now;
	return true;
}