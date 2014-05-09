#pragma once
#include "includes.h"
#include "GameEntityList.h"
#include "Observers.h"

class BulletList : public GameEntityList
{
	float speed;
	e::XMFLOAT2 dir;
	GameObservers::ObserverScopeRef or;
public:
	BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float speed, e::XMFLOAT2 dir, int spawnEvent, e::XMFLOAT4 color = e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	BulletList(GameEntityList &&other)
		:GameEntityList(e::move(other)){}

	void Loop(int frame);
};