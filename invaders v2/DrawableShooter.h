#pragma once
#include "includes.h"
#include "ColorDrawableEntity.h"
#include "Shooter.h"

class DrawableShooter : public ColorDrawableEntity, public Shooter
{
public:
	DrawableShooter(e::XMVECTOR pos, ColorModel &model, ColorShader &shader, float fireRate,
		float speed, e::XMFLOAT4 color = e::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), float scale = 1.0f)
		:ColorDrawableEntity(pos, model, shader, color, scale), Shooter(fireRate, speed){}
	virtual ~DrawableShooter(){}
};