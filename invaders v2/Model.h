#pragma once

#include "Globals.h"

using namespace std;
struct Model
{
	vector<VertexType> vertices;
	vector<int> indices;
	D3DXVECTOR2 hitbox;
};