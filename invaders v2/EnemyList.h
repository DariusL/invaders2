#pragma once
#include "includes.h"
#include "GameEntityList.h"
#include "Observers.h"

class EnemyList : public GameEntityList
{
public:
	EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount) :GameEntityList(device, model, shader, maxObjectCount){}
	EnemyList(GameEntityList &&other):GameEntityList(e::move(other)){}

protected:
	void OnRemove(const e::shared_ptr<GameEntity> entity){ Observers::Notify(Observers::EVENT_ENEMY_DEATH, entity); }
};