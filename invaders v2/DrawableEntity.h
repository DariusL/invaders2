#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "ColorShader.h"
#include "Model.h"
#include "includes.h"
#include "Utils.h"

template<class vt, class sh>
class DrawableEntity : public Entity, public IDrawableObject
{
protected:
	Model<vt> &model;
	XMFLOAT4X4 moveMatrix, scaleMatrix;
	float scale;
	sh &shader;
public:
	DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float scale = 1.0f);
	DrawableEntity(XMVECTOR pos, Model<vt> &model, sh &shader, float scale = 1.0f);
	DrawableEntity(DrawableEntity &&other);
	virtual ~DrawableEntity(void);

	virtual void Render(const RenderParams &renderParams);
	virtual void SetScale(float scale);
protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef DrawableEntity<VertexType, ColorShader> SimpleDrawableEntity;

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float scale)
: Entity(pos, model.GetSize()), model(model), shader(shader), scale(scale)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(XMVECTOR pos, Model<vt> &model, sh &shader, float scale)
: Entity(pos, model.GetSize()), model(model), shader(shader), scale(scale)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(forward<DrawableEntity>(other)), Entity(forward<DrawableEntity>(other)),
model(move(other.model)), shader(move(other.shader)), 
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
	if(!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, scale * world);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class vt, class sh>
bool DrawableEntity<vt, sh>::Update(ID3D11DeviceContext *context)
{
	if(dead)
		return false;

	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));
	XMStoreFloat4x4(&scaleMatrix, XMMatrixScaling(scale, scale, scale));

	return true;
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::SetScale(float scale)
{
	this->scale = scale;
}