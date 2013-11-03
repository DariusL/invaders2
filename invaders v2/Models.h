#pragma once

#include "Globals.h"

using namespace std;

template<class T>
struct Model
{
	vector<T> vertices;
	vector<int> indices;
	D3DXVECTOR2 hitbox;
};

typedef Model<VertexType> ColorModel;
typedef Model<NormalMappedVertexType> NormalMappedModel;
typedef Model<NormalVertexType> NormalModel;
typedef Model<TextureVertexType> TexturedModel;