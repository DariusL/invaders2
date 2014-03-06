#pragma once
#include "includes.h"
#include "GameEntity.h"

class Collider
{
	e::vector<e::shared_ptr<GameEntity>> entities;
public:
	void Insert(e::shared_ptr<GameEntity> entity);
	void Update();
private:
	void Collide(GameEntity *first, GameEntity *second);
};