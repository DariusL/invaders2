#pragma once

#include "includes.h"
#include "Globals.h"
#include "IPhysicalInfo.h"

using namespace DirectX;

class Entity : public IPhysicalInfo
{
public:
	XMFLOAT3 pos;
	XMFLOAT3 nextPos;
	XMFLOAT3 speed;
	float mass;

	Entity(XMFLOAT3 start = ZeroVec3, XMFLOAT3 speed = ZeroVec3, float mass = 1000000.0f) :pos(start), speed(speed), mass(mass){}
	virtual ~Entity(void){}

	const XMFLOAT3 &GetPos() const {return pos;}
	float GetMass() const { return mass; }
};

