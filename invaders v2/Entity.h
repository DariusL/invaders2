#pragma once

#include "includes.h"
#include "Globals.h"

class Entity
{
protected:
	e::XMFLOAT3 pos;
public:
	Entity(e::XMFLOAT3 start);
	Entity(e::XMVECTOR start);
	virtual ~Entity(void){}

	e::XMFLOAT3 GetPos() const { return pos; }
	void MoveBy(e::XMFLOAT3 step);
	void MoveBy(e::XMVECTOR step);
	void MoveTo(e::XMFLOAT3 pos);
	void MoveTo(e::XMVECTOR pos);
};

