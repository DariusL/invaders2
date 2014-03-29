#pragma once
#include "includes.h"
#include "Globals.h"
#include "Model.h"

class Gun
{
	int spawnEvent;
	uint firePeriod;
	uint lastFired;
	e::XMFLOAT2 bulletSize;
	float off;
public:
	Gun(int spawnEvent, uint firePeriod, float off, ColorModel &model);
	void Fire(e::XMVECTOR gunPos);
	static e::unique_ptr<Gun> PlayerGun(uint firePeriod);
	static e::unique_ptr<Gun> EnemyGun(uint firePeriod);
};