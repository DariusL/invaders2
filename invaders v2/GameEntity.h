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
	e::XMFLOAT4 color;
	static e::default_random_engine gen;
public:
	GameEntity(e::XMVECTOR pos = Utils::VectorSet(), int health = 1, int damage = 0, float speed = 0.0f, e::XMFLOAT2 size = ZeroVec2, e::unique_ptr<Gun> gun = nullptr, e::XMFLOAT4 color = Gray);
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

	void SetHealth(int health){ this->health = health; }
	void SetMaxHealth(int maxHealth){ this->maxHealth = health; }

	int GetHealth(){ return health; }
	int GetMaxHealth(){ return maxHealth; }

	const e::XMFLOAT4 &GetColor(){ return color; }
	
	float GetSpeed(){ return speed; }

	static e::shared_ptr<GameEntity> MakeEnemy(e::XMVECTOR pos, int model, int difficulty);
};