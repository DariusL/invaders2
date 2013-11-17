#pragma once

#include "includes.h"

class IPhysicalInfo
{
public:
	virtual const DirectX::XMFLOAT3 &GetPos() const = 0;
	virtual float GetMass() const = 0;
};