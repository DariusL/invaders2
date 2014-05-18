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
	float off, bulletSpeed;
	int damage;
public:
	Gun(int spawnEvent, uint firePeriod, float off, int damage, ColorModel &model);
	void Fire(e::XMVECTOR gunPos);
	int GetDamage(){ return damage; }
	void SetDamage(int damage){ this->damage = damage; }
	uint GetFirePeriod(){ return firePeriod; }
	void SetFirePeriod(uint firePeriod){ this->firePeriod = firePeriod; this->bulletSpeed = 1.0f / firePeriod * 40.0f; lastFired = 0; }
	static e::unique_ptr<Gun> PlayerGun(uint firePeriod, int damage);
	static e::unique_ptr<Gun> EnemyGun(uint firePeriod, int damage);
};