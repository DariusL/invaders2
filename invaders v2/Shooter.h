#pragma once
#include "entity.h"
class Shooter : public Entity
{
		//per second
	float fireRate;
	float lastFired;
public:
	Shooter(void);
	Shooter(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed, float fireRate);
	~Shooter(void);

	void SetFireRate(float fireRate){this->fireRate = fireRate;}
	float GetFireRate() const {return fireRate;}

	void Fire(){lastFired = std::clock() / float(CLOCKS_PER_SEC);}
	float GetLastFired() const {return lastFired;}
};

