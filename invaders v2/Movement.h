#pragma once
#include "includes.h"

class Movement
{
	e::XMFLOAT3 start, end, off;
	int startTime;
	int currentTime;
	int length;
public:
	Movement(e::XMFLOAT3 start, e::XMFLOAT3 end, int length);
	Movement(e::XMVECTOR start, e::XMVECTOR end, int length);
	void Loop(int frame);
	/*
		hacky, used by Grid::AddRow to offset the movement
	*/
	void MoveBy(e::XMVECTOR off);
	e::XMVECTOR GetPos();
	e::XMVECTOR GetDir();
	bool IsOver();
};