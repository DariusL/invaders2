#include "includes.h"
#include "GameEntity.h"

GameEntity::GameEntity(e::XMFLOAT3 pos, e::XMFLOAT2 size, uint health)
:Entity(pos), size(size), health(health), maxHealth(health)
{
}

GameEntity::GameEntity(e::XMVECTOR pos, e::XMFLOAT2 size, uint health)
:Entity(pos), size(size), health(health), maxHealth(health)
{
}

bool GameEntity::CollidesWith(const GameEntity &other)
{
	return (abs(pos.x - other.pos.x) <= (size.x + other.size.x) / 2.0f)
		&& (abs(pos.y - other.pos.y) <= (size.y + other.size.y) / 2.0f);
}