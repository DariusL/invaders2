#pragma once
#include "includes.h"

class Movement
{
	e::XMFLOAT3 start, end, off;
	int startTime;
	int length;
public:
	Movement(e::XMFLOAT3 start, e::XMFLOAT3 end, int length);
	Movement(e::XMVECTOR start, e::XMVECTOR end, int length);
	e::XMVECTOR GetPos();
	e::XMVECTOR GetDir();
	bool IsOver();
};