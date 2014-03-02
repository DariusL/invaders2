#pragma once
#include "includes.h"
#include "Entity.h"

class GameEntity : public Entity
{
	uint health;
	uint maxHealth;
	e::XMFLOAT2 size;
public:
	GameEntity(e::XMFLOAT3 pos, e::XMFLOAT2 size, uint health);
	GameEntity(e::XMVECTOR pos, e::XMFLOAT2 size, uint health);
	virtual ~GameEntity(){}

	const e::XMFLOAT2 &GetSize() const { return size; }
	bool IsDead() const { return health <= 0; }
	bool CollidesWith(const GameEntity &other);
};