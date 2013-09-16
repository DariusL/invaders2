#pragma once

#include "Globals.h"

using namespace std;
struct NormalModel
{
	vector<NormalVertexType> vertices;
	vector<int> indices;
	D3DXVECTOR2 hitbox;
};