#pragma once
#include "GameEntity.h"
#include "IDrawableObject.h"
#include "ColorShader.h"
#include "Model.h"
#include "includes.h"
#include "Utils.h"

template<class vt, class sh>
class DrawableEntity : public GameEntity, public IDrawableObject
{
protected:
	Model<vt> &model;
	e::XMFLOAT4X4 moveMatrix, scaleMatrix;
	float scale;
	sh &shader;
public:
	DrawableEntity(e::XMVECTOR pos, Model<vt> &model, sh &shader, int fireRate, float speed, int health, int damage, float scale = 1.0f);
	DrawableEntity(e::XMVECTOR pos, Model<vt> &model, sh &shader, float scale = 1.0f);
	DrawableEntity(DrawableEntity &&other);
	virtual ~DrawableEntity(void);

	virtual void Render(const RenderParams &renderParams);
	virtual void SetScale(float scale);
protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef DrawableEntity<VertexType, ColorShader> SimpleDrawableEntity;


template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(e::XMVECTOR pos, Model<vt> &model, sh &shader, int fireRate, float speed, int health, int damage, float scale)
: GameEntity(pos, model.GetSize(), health, damage, fireRate, speed), model(model), shader(shader), scale(scale)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(e::XMVECTOR pos, Model<vt> &model, sh &shader, float scale)
: GameEntity(pos, model.GetSize()), model(model), shader(shader), scale(scale)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(e::forward<DrawableEntity>(other)), GameEntity(e::forward<DrawableEntity>(other)),
model(e::move(other.model)), shader(e::move(other.shader)),
scale(other.scale)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::~DrawableEntity(void)
{
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	e::XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	e::XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, scale * world);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class vt, class sh>
bool DrawableEntity<vt, sh>::Update(ID3D11DeviceContext *context)
{
	using namespace e;
	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));
	XMStoreFloat4x4(&scaleMatrix, XMMatrixScaling(scale, scale, scale));

	return true;
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::SetScale(float scale)
{
	this->scale = scale;
}