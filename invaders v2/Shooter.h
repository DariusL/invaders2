#pragma once
#include "includes.h"
class Shooter
{
	//fiziks
	//per second
	float fireRate;
	float lastFired;
	float speed;
public:
	Shooter(float fireRate, float speed);
	~Shooter(void);

	float GetFireRate() const {return fireRate;}
	float GetSpeed() const { return speed; }

	bool Fire();
	float GetLastFired() const {return lastFired;}

	Shooter &operator=(Shooter &&other)
	{
		std::swap(fireRate, other.fireRate);
		std::swap(lastFired, other.lastFired);
	}
};