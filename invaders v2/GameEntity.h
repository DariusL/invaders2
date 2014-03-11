#pragma once
#include "includes.h"
#include "GameEntity.h"
#include "Globals.h"

class GameEntity
{
protected:
	//base
	e::XMFLOAT3 pos;
	//game
	int health;
	int maxHealth;
	int damage;
	float speed;
	e::XMFLOAT2 size;

	//shooter
	int fireRate;
	int lastFired;
public:
	GameEntity(e::XMVECTOR pos, e::XMFLOAT2 size = ZeroVec2, int health = 0, int damage = 0, int fireRate = 0, float speed = 0.0f);
	virtual ~GameEntity(){}

	const e::XMFLOAT2 &GetSize() const { return size; }
	bool IsDead() const { return health <= 0; }
	bool CollidesWith(const GameEntity &other);

	void Kill(){ health = 0; }
	int GetDamage() const { return damage; }
	void HitFor(int damange){ health -= damage; }

	int GetFireRate() const { return fireRate; }
	float GetSpeed() const { return speed; }

	bool Fire();
	int GetLastFired() const { return lastFired; }

	e::XMFLOAT3 GetPos() const { return pos; }
	void MoveBy(e::XMFLOAT3 step);
	void MoveBy(e::XMVECTOR step);
	void MoveTo(e::XMFLOAT3 pos);
	void MoveTo(e::XMVECTOR pos);
};