#pragma once

#include "includes.h"
#include "Globals.h"

using namespace DirectX;

class Entity
{
protected:
	XMFLOAT3 pos;
	XMFLOAT2 size;

	float deathTime;
	bool dead;
public:
	Entity(XMFLOAT3 start, XMFLOAT2 size, bool dead = false);
	Entity(XMVECTOR start, XMFLOAT2 size, bool dead = false);
	virtual ~Entity(void);

	XMFLOAT3 GetPos() const {return pos;}
	void MoveBy(XMFLOAT3 step);
	void MoveBy(XMVECTOR step);
	void MoveTo(XMFLOAT3 pos);
	void MoveTo(XMVECTOR pos);

	void SetSize(XMFLOAT2 size){this->size = size;}
	XMFLOAT2 GetSize() const { return size; }

	float GetDeathTime() const {return deathTime;}

	bool IsDead() const {return dead;}
	void Kill();
	void Revive(){dead = false;}
};

