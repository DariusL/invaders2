#include "includes.h"
#include "ColorDrawableEntity.h"


ColorDrawableEntity::ColorDrawableEntity(e::XMVECTOR pos, ColorModel &model, ColorShader &shader, e::XMFLOAT4 color, float scale)
:DrawableEntity(pos, model, shader, scale), color(color)
{
}

ColorDrawableEntity::ColorDrawableEntity(e::XMVECTOR pos, int fireRate, float speed, int health, int damage, ColorModel &model, ColorShader &shader, e::XMFLOAT4 color, float scale)
: DrawableEntity(pos, model, shader, fireRate, speed, health, damage, scale), color(color)
{

}

void ColorDrawableEntity::Render(const RenderParams &params)
{
	using namespace e;
	if (!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, scale * world, color);
	shader.RenderShader(params.context, model.GetIndexCount());
}