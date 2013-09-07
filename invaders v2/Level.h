#pragma once

#include <vector>

#include "Globals.h"

using namespace std;

struct Level
{
	int gridWidth;
	int gridHeight;
	vector<int> enemies;
	D3DXVECTOR2 gap;
};