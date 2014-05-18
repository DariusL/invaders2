#pragma once
#include "includes.h"
#include "GameEntityList.h"
#include "Observers.h"

class EnemyList : public GameEntityList
{
public:
	EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float scale = 1.0f) 
		:GameEntityList(device, model, shader, maxObjectCount, scale){}
	EnemyList(GameEntityList &&other):GameEntityList(e::move(other)){}

protected:
	void OnRemove(const e::shared_ptr<GameEntity> entity){ GameObservers::Notify(GAME_EVENT_ENEMY_DEATH, entity); }
};