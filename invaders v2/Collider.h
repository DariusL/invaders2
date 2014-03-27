#pragma once
#include "includes.h"
#include "GameEntity.h"

class Collider
{
	e::vector<e::shared_ptr<GameEntity>> first;
	e::vector<e::shared_ptr<GameEntity>> second;
public:
	Collider();
	void InsertFirst(e::shared_ptr<GameEntity> entity);
	void InsertSecond(e::shared_ptr<GameEntity> entity);
	void Update();
private:
	void Collide(GameEntity *first, GameEntity *second);
};