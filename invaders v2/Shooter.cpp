#include "Shooter.h"


Shooter::Shooter(void)
{
}


Shooter::~Shooter(void)
{
}

Shooter::Shooter(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed, float fireRate)
{
	this->pos = start;
	this->size = size;
	this->speed = speed;
	this->fireRate = fireRate;
	this->lastFired = 0;
	this->dead = false;
}