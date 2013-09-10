#pragma once

#include <vector>

#include "Globals.h"

using namespace std;
struct NormalModel
{
	vector<NormalVertexType> vertices;
	int vertexCount;
	vector<int> indices;
	int indexCount;
	D3DXVECTOR2 hitbox;
};