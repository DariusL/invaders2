#pragma once

#include "includes.h"
#include "Globals.h"

class Entity
{
protected:
	e::XMFLOAT3 pos;
	e::XMFLOAT2 size;

	float deathTime;
	bool dead;
public:
	Entity(e::XMFLOAT3 start, e::XMFLOAT2 size, bool dead = false);
	Entity(e::XMVECTOR start, e::XMFLOAT2 size, bool dead = false);
	virtual ~Entity(void);

	e::XMFLOAT3 GetPos() const { return pos; }
	void MoveBy(e::XMFLOAT3 step);
	void MoveBy(e::XMVECTOR step);
	void MoveTo(e::XMFLOAT3 pos);
	void MoveTo(e::XMVECTOR pos);

	void SetSize(e::XMFLOAT2 size){ this->size = size; }
	e::XMFLOAT2 GetSize() const { return size; }

	float GetDeathTime() const {return deathTime;}

	bool IsDead() const {return dead;}
	void Kill();
	void Revive(){dead = false;}
};

