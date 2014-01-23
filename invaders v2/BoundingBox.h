#pragma once
#include "includes.h"
class BoundingBox
{
	bool empty;
	DirectX::XMFLOAT3 minv, maxv;
public:
	BoundingBox():empty(true){}
	void Add(const DirectX::XMFLOAT3 &vert);
	DirectX::XMFLOAT3 GetSize();
};

