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
