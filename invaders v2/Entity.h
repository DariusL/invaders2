#pragma once

#include "includes.h"
#include "Globals.h"

using namespace DirectX;

class Entity
{
protected:
	XMFLOAT3 pos;
	XMFLOAT2 size;

	float speed;
	float deathTime;
	bool dead;
public:
	Entity(XMFLOAT3 start = ZeroVec3, float speed = 0.0f, XMFLOAT2 size = XMFLOAT2(0.0f, 0.0f));
	virtual ~Entity(void);

	XMFLOAT3 GetPos() const {return pos;}
	void MoveBy(XMFLOAT3 step);
	void MoveTo(XMFLOAT3 pos);

	float GetLeftBorder() const {return pos.x - size.x / 2;}
	float GetRightBorder() const {return pos.x + size.x / 2;}
	float GetTopBorder() const {return pos.y + size.y / 2;}
	float GetBottomBorder() const {return pos.y - size.y / 2;}

	void SetSize(XMFLOAT2 size){this->size = size;}

	void SetSpeed(float speed){this->speed = speed;}
	float GetSpeed() const {return speed;}

	float GetDeathTime() const {return deathTime;}

	bool IsDead() const {return dead;}
	void Kill();
	void Revive(){dead = false;}
	
	bool CollideWith(const Entity &other) const;
	bool CollideWithAndKill(const Entity &other);
	bool CollideWithAndKillBoth(Entity &other);
};

