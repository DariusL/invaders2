#pragma once
#include "includes.h"
#include "IInstance.h"
#include "DrawableShooter.h"

class Enemy : public DrawableShooter, public IInstance<e::XMFLOAT3>
{
public:
	Enemy(XMVECTOR pos, ColorModel &model, ColorShader &shader, float fireRate,
		float speed, e::XMFLOAT4 color = e::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), float scale = 1.0f)
		:DrawableShooter(pos, model, shader, fireRate, speed, color, scale){}
	virtual ~Enemy(){}
	e::XMFLOAT3 GetInstanceData(){ return GetPos(); }
};