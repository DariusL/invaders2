#pragma once
#include "GameEntity.h"
#include "IDrawableObject.h"
#include "ColorShader.h"
#include "Model.h"
#include "includes.h"
#include "Utils.h"

template<class vt, class sh, class en>
class DrawableEntity : public IDrawableObject
{
protected:
	Model<vt> *model;
	e::XMFLOAT4X4 moveMatrix, scaleMatrix;
	float scale;
	sh *shader;
	e::shared_ptr<en> entity;
public:
	DrawableEntity(Model<vt> &model, sh &shader, e::shared_ptr<en> entity, float scale = 1.0f);
	DrawableEntity(DrawableEntity &&other);
	DrawableEntity &operator=(DrawableEntity &&other);
	virtual ~DrawableEntity(void);

	virtual void Render(const RenderParams &renderParams);
	virtual void SetScale(float scale);
	e::shared_ptr<en> &GetEntity(){ return entity; }
	e::XMFLOAT2 GetSize() { return model->GetSize(); }
	void SetModel(Model<vt> &model){ this->model = &model; }
protected:
	virtual bool Update(ID3D11DeviceContext *context);
};

typedef DrawableEntity<VertexType, ColorShader, GameEntity> SimpleDrawableEntity;

template<class vt, class sh, class en>
DrawableEntity<vt, sh, en>::DrawableEntity(Model<vt> &model, sh &shader, e::shared_ptr<en> entity, float scale)
: model(&model), shader(&shader), scale(scale), entity(entity)
{
}

template<class vt, class sh, class en>
DrawableEntity<vt, sh, en>::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(e::move(other)), entity(e::move(other.entity)),
model(other.model), shader(other.shader),
scale(other.scale)
{
}
template<class vt, class sh, class en>
DrawableEntity<vt, sh, en> &DrawableEntity<vt, sh, en>::operator=(DrawableEntity &&other)
{
	if (this != &other)
	{

		model = other.model;
		shader = other.shader;
		scale = other.scale;
		moveMatrix = other.moveMatrix;
		scaleMatrix = other.scaleMatrix;
		entity = e::move(other.entity);
	}
	return *this;
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
	model->Set(params.context);
	e::XMMATRIX scale = XMLoadFloat4x4(&scaleMatrix);
	e::XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader->SetShaderParameters(params, scale * world);
	shader->RenderShader(params.context, model->GetIndexCount());
}

template<class vt, class sh, class en>
bool DrawableEntity<vt, sh, en>::Update(ID3D11DeviceContext *context)
{
	if (entity->IsDead())
		return false;
	using namespace e;
	auto pos = entity->GetPos();
	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));
	XMStoreFloat4x4(&scaleMatrix, XMMatrixScaling(scale, scale, scale));

	return true;
}

template<class vt, class sh, class en>
void DrawableEntity<vt, sh, en>::SetScale(float scale)
{
	this->scale = scale;
}