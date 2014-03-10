#pragma once
#include "includes.h"
#include "DrawableEntity.h"

class ColorDrawableEntity : public DrawableEntity<VertexType, ColorShader, Entity>
{
	e::XMFLOAT4 color;
public:
	ColorDrawableEntity(e::XMVECTOR pos, ColorModel &model, ColorShader &shader, e::XMFLOAT4 color = e::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), float scale = 1.0f);
	virtual ~ColorDrawableEntity(){}
	virtual void Render(const RenderParams &params);
};