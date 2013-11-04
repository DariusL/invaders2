#pragma once
#pragma warning(disable : 4005)

#include "Shooter.h"
#include "Models.h"
#include "DrawableEntity.h"
#include "ColorShader.h"
#include "includes.h"

using namespace std;
class DrawableShooter : public Shooter, public DrawableEntity<VertexType, ColorShader>
{
public:
	DrawableShooter(float speed, float fireRate, shared_ptr<ColorModel> model, shared_ptr<ColorShader> shader)
		:DrawableEntity(D3DXVECTOR3(), model, shader, speed), Shooter(fireRate){}
};