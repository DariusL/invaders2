#pragma once

#include "Globals.h"

using namespace std;
struct TexturedNormalModel
{
	vector<NormalMappedVertexType> vertices;
	vector<int> indices;
	D3DXVECTOR2 hitbox;
};