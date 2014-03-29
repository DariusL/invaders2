#pragma once
#include "includes.h"
#include "Gun.h"
#include "Globals.h"
#include "Utils.h"

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

	e::unique_ptr<Gun> gun;
public:
	GameEntity(e::XMVECTOR pos = Utils::VectorSet(), int health = 1, int damage = 0, float speed = 0.0f, e::XMFLOAT2 size = ZeroVec2, e::unique_ptr<Gun> gun = nullptr);
	virtual ~GameEntity(){}

	const e::XMFLOAT2 &GetSize() const { return size; }
	void SetSize(e::XMFLOAT2 size){ this->size = size; }
	bool IsDead() const { return health <= 0; }
	bool CollidesWith(const GameEntity &other);

	void Kill(){ health = 0; }
	int GetDamage() const { return damage; }
	void HitFor(int damange){ health -= damage; }

	float GetSpeed() const { return speed; }

	void Fire();

	e::XMFLOAT3 GetPos() const { return pos; }
	void MoveBy(e::XMFLOAT3 step);
	void MoveBy(e::XMVECTOR step);
	void MoveTo(e::XMFLOAT3 pos);
	void MoveTo(e::XMVECTOR pos);
};