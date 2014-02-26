#pragma once
#include "includes.h"

class Movement
{
	typedef e::chrono::system_clock Clock;
	e::XMFLOAT3 start, end, off;
	e::chrono::time_point<Clock> startTime;
	e::chrono::milliseconds length;
public:
	Movement(e::XMFLOAT3 start, e::XMFLOAT3 end, e::chrono::milliseconds length);
	e::XMVECTOR GetPos();
	bool IsOver();
};