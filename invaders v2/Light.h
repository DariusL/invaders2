#pragma once
#include "Model.h"
#include "Globals.h"
#include "DrawableEntity.h"
using namespace std;

class Light : public SimpleDrawableEntity
{
	D3DXVECTOR4 color;
public:
	Light(D3DXVECTOR3 pos, D3DXVECTOR4 color, ColorModel &model, ColorShader &shader)
		:DrawableEntity(pos, model, shader)
	{
		this->color = color;
	}
	~Light(void){}

	const D3DXVECTOR4 &GetColor(){return color;}
};