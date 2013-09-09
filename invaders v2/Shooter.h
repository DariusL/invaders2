#pragma once
#include "entity.h"
class Shooter : public Entity
{
	//fiziks
	//per second
	float fireRate;
	float lastFired;

public:
	Shooter(D3DXVECTOR2 size, float speed, float fireRate);
	~Shooter(void);

	void SetFireRate(float fireRate){this->fireRate = fireRate;}
	float GetFireRate() const {return fireRate;}

	bool Fire();
	float GetLastFired() const {return lastFired;}
};

