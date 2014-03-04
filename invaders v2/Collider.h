#pragma once
#include "includes.h"
#include "GameEntity.h"

class Collider
{
	e::vector<e::shared_ptr<GameEntity>> entities;
public:
	void Add(e::shared_ptr<GameEntity> entity);
	void Update();
};