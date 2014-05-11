#pragma once
#include "includes.h"
#include "GameEntityList.h"
#include "Observers.h"

class BulletList : public GameEntityList
{
	e::XMFLOAT2 dir;
	GameObservers::ObserverScopeRef or;
public:
	BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, e::XMFLOAT2 dir, int spawnEvent);
	BulletList(GameEntityList &&other)
		:GameEntityList(e::move(other)){}

	void Loop(int frame);
};