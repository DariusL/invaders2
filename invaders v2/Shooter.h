#pragma once
#include "includes.h"
class Shooter
{
	//fiziks
	//per second
	float fireRate;
	float lastFired;

public:
	Shooter(float fireRate);
	~Shooter(void);

	void SetFireRate(float fireRate){this->fireRate = fireRate;}
	float GetFireRate() const {return fireRate;}

	bool Fire();
	float GetLastFired() const {return lastFired;}

	Shooter &operator=(Shooter &&other)
	{
		std::swap(fireRate, other.fireRate);
		std::swap(lastFired, other.lastFired);
	}
};