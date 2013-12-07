#pragma once
#include "Model.h"
#include "Globals.h"
#include "DrawableEntity.h"
using namespace std;

class Light : public SimpleDrawableEntity
{
	XMFLOAT4 color;
public:
	Light(XMFLOAT3 pos, XMFLOAT4 color, ColorModel &model, ColorShader &shader)
		:DrawableEntity(pos, model, shader), color(color)
	{
	}
	~Light(void){}

	const XMFLOAT4 &GetColor(){return color;}
};