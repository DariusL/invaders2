#pragma once

#include "Shooter.h"
#include "Model.h"
#include "DrawableEntity.h"
#include "ColorShader.h"
#include "includes.h"

using namespace std;
class DrawableShooter : public Shooter, public SimpleDrawableEntity
{
public:
	DrawableShooter(float speed, float fireRate, ColorModel &model, ColorShader &shader)
		:DrawableEntity(XMFLOAT3(), model, shader, speed), Shooter(fireRate){}

	DrawableShooter(DrawableShooter &&other)
		:SimpleDrawableEntity(forward<DrawableShooter>(other)), Shooter(forward<DrawableShooter>(other)){}
};