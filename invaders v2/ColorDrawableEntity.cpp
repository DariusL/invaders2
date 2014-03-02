#include "includes.h"
#include "ColorDrawableEntity.h"
using namespace e;
ColorDrawableEntity::ColorDrawableEntity(XMVECTOR pos, ColorModel &model, ColorShader &shader, e::XMFLOAT4 color, float scale)
:DrawableEntity(pos, model, shader, scale), color(color)
{
}

void ColorDrawableEntity::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, scale * world, color);
	shader.RenderShader(params.context, model.GetIndexCount());
}