#pragma once
#include "Entity.h"
#include "Shooter.h"

class ShooterEntity : public Entity, public Shooter
{
public:
	ShooterEntity(e::XMFLOAT3 start, e::XMFLOAT2 size, float fireRate, float speed)
		:Entity(start), Shooter(fireRate, speed){}
	ShooterEntity(e::XMVECTOR start, e::XMFLOAT2 size, float fireRate, float speed)
		:Entity(start), Shooter(fireRate, speed){}
};