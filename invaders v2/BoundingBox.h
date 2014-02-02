#pragma once
#include "includes.h"
class BoundingBox
{
	bool empty;
	DirectX::XMFLOAT3 minv, maxv;
public:
	BoundingBox():empty(true){}
	void Add(const DirectX::XMFLOAT3 &vert);
	DirectX::XMFLOAT3 GetSize() const;
	DirectX::XMFLOAT3 GetCenter() const;
	DirectX::XMFLOAT3 GetMin() const { return empty ? ZeroVec3 : minv; }
	DirectX::XMFLOAT3 GetMax() const { return empty ? ZeroVec3 : maxv; }
	void Move(DirectX::XMFLOAT3 offset);
};