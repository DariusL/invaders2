#pragma once
#include <memory>
#include "Globals.h"
using namespace std;

struct Level
{
	int gridWidth;
	int gridHeight;
	unique_ptr<int[]> enemies;
	D3DXVECTOR2 gap;
};