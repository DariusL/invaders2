#pragma once
#include "includes.h"
#include "GameEntityList.h"

class BulletList : public GameEntityList
{
	float speed;
	e::XMFLOAT2 dir;
public:
	BulletList(ID3D11Device *device, ColorModel &model, ColorInstancedShader &shader, int maxObjectCount, float speed, e::XMFLOAT2 dir)
		:GameEntityList(device, model, shader, maxObjectCount), speed(speed), dir(dir){}
	BulletList(GameEntityList &&other)
		:GameEntityList(e::move(other)){}

	void Loop(int frame);
};