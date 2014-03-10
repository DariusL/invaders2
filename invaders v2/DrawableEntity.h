#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "ColorShader.h"
#include "Model.h"
#include "includes.h"
#include "Utils.h"

template<class vt, class sh, class en>
class DrawableEntity : public IDrawableObject
{
protected:
	en entity;
	Model<vt> &model;
	e::XMFLOAT4X4 moveMatrix, scaleMatrix;
	float scale;
	sh &shader;
public:
	DrawableEntity(en &&entity, Model<vt> &model, sh &shader, float scale = 1.0f);
	DrawableEntity(DrawableEntity &&other);
	en &GetEntity(){ return entity; }
	virtual ~DrawableEntity(void);

	virtual void Render(const RenderParams &renderParams);
	virtual void SetScale(float scale);
protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef DrawableEntity<VertexType, ColorShader, Entity> SimpleDrawableEntity;

template<class vt, class sh, class en>
DrawableEntity<vt, sh, en>::DrawableEntity(en &&entity, Model<vt> &model, sh &shader, float scale)
: entity(e::forward<en>(entity)), model(model), shader(shader), scale(scale)
{
}

template<class vt, class sh, class en>
DrawableEntity<vt, sh, en>::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(e::forward<DrawableEntity>(other)), entity(e::forward<DrawableEntity>(other.entity)),
model(e::move(other.model)), shader(e::move(other.shader)),
scale(other.scale)
{
}

template<class vt, class sh, class en>
DrawableEntity<vt, sh, en>::~DrawableEntity(void)
{
}

template<class vt, class sh, class en>
void DrawableEntity<vt, sh, en>::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	e::XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	e::XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, scale * world);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class vt, class sh, class en>
bool DrawableEntity<vt, sh, en>::Update(ID3D11DeviceContext *context)
{
	auto pos = entity.GetPos();
	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));
	XMStoreFloat4x4(&scaleMatrix, XMMatrixScaling(scale, scale, scale));

	return true;
}

template<class vt, class sh, class en>
void DrawableEntity<vt, sh, en>::SetScale(float scale)
{
	this->scale = scale;
}