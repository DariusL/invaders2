#pragma once
#include "Entity.h"
#include "Shooter.h"

class ShooterEntity : public Entity, public Shooter
{
public:
	ShooterEntity(XMFLOAT3 start, XMFLOAT2 size, float fireRate, float speed, bool dead = false)
		:Entity(start, size, dead), Shooter(fireRate, speed){}
	ShooterEntity(XMVECTOR start, XMFLOAT2 size, float fireRate, float speed, bool dead = false)
		:Entity(start, size, dead), Shooter(fireRate, speed){}
};