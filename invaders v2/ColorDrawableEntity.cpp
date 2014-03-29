#include "includes.h"
#include "ColorDrawableEntity.h"


ColorDrawableEntity::ColorDrawableEntity(ColorModel &model, ColorShader &shader, e::shared_ptr<GameEntity> entity, e::XMFLOAT4 color, float scale)
:DrawableEntity(model, shader, entity, scale), color(color)
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