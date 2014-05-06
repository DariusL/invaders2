#pragma once
#include "includes.h"
#include "GameEntityList.h"
#include "Observers.h"

class EnemyList : public GameEntityList
{
public:
	EnemyList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT4 color = e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)) 
		:GameEntityList(device, model, shader, maxObjectCount, color){}
	EnemyList(GameEntityList &&other):GameEntityList(e::move(other)){}

protected:
	void OnRemove(const e::shared_ptr<GameEntity> entity){ GameObservers::Notify(GAME_EVENT_ENEMY_DEATH, entity); }
};