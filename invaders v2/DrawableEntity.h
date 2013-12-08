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
	XMFLOAT4X4 moveMatrix;
	sh &shader;
public:
	DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float speed = 0.0f);
	DrawableEntity(DrawableEntity &&other);
	virtual ~DrawableEntity(void);

	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Render(const RenderParams &renderParams);
protected:
	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
};

typedef DrawableEntity<VertexType, ColorShader> SimpleDrawableEntity;

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float speed)
: Entity(pos, speed), model(model), shader(shader)
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(forward<DrawableEntity>(other)), Entity(forward<DrawableEntity>(other)),
model(move(other.model)), shader(move(other.shader)), 
moveMatrix(move(other.moveMatrix))
{
}

template<class vt, class sh>
DrawableEntity<vt, sh>::~DrawableEntity(void)
{
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, world);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class vt, class sh>
bool DrawableEntity<vt, sh>::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	return true;
}