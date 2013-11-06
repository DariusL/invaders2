#pragma once

#include "Globals.h"

using namespace std;

template<class T>
struct Model : NonCopyable
{
	vector<T> vertices;
	vector<int> indices;
	D3DXVECTOR2 hitbox;

	Model(){}
	Model(Model &&other);
	Model &operator=(Model &&other);
};

typedef Model<VertexType> ColorModel;
typedef Model<NormalMappedVertexType> NormalMappedModel;
typedef Model<NormalVertexType> NormalModel;
typedef Model<TextureVertexType> TexturedModel;

template<class T>
Model<T>::Model(Model &&other)
	:vertices(move(other.vertices)), indices(move(other.indices))
{
	D3DXVECTOR2 temp(hitbox);
	hitbox = other.hitbox;
	other.hitbox = temp;
}

template<class T>
Model<T> &Model<T>::operator=(Model &&other)
{
	if(this != &other)
	{
		vertices = move(other.vertices);
		indices = move(other.indices);
		D3DXVECTOR2 temp(hitbox);
		hitbox = other.hitbox;
		other.hitbox = temp;
	}
	return *this;
}