#pragma once
#include "Models.h"
#include "Globals.h"
#include "DrawableEntity.h"
using namespace std;

class Light : public SimpleDrawableEntity
{
	D3DXVECTOR4 color;
public:
	Light(D3DXVECTOR3 pos, D3DXVECTOR4 color, shared_ptr<ColorModel> model, shared_ptr<ColorShader> shader)
		:DrawableEntity(pos, model, shader)
	{
		this->color = color;
	}
	~Light(void){}

	const D3DXVECTOR4 &GetColor(){return color;}
};