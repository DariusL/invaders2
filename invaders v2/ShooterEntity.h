#pragma once
#include "GameEntity.h"
#include "Shooter.h"

class ShooterEntity : public GameEntity, public Shooter
{
public:
	ShooterEntity(e::XMFLOAT3 start, e::XMFLOAT2 size, float fireRate, float speed)
		:GameEntity(start, size, 1), Shooter(fireRate, speed){}
	ShooterEntity(e::XMVECTOR start, e::XMFLOAT2 size, float fireRate, float speed)
		:GameEntity(start, size, 1), Shooter(fireRate, speed){}
};