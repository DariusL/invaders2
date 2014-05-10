#pragma once
#include "includes.h"
#include "DrawableEntity.h"

class ColorDrawableEntity : public DrawableEntity<VertexType, ColorShader, GameEntity>
{
	e::XMFLOAT4 color;
public:
	ColorDrawableEntity(ColorModel &model, ColorShader &shader, e::shared_ptr<GameEntity> entity, e::XMFLOAT4 color = e::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), float scale = 1.0f);
	ColorDrawableEntity(ColorDrawableEntity&& other) :DrawableEntity(e::move(other)), color(other.color){}
	virtual ~ColorDrawableEntity(){}
	virtual void Render(RenderParams &params);
};