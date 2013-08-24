#pragma once
#include <memory>
using namespace std;

struct Level
{
	int gridWidth;
	int gridHeight;
	unique_ptr<int[]> enemies;
};