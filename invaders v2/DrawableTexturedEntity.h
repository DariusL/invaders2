#pragma once

#include "includes.h"
#include "DrawableEntity.h"
#include "TextureShader.h"
#include "Model.h"

template<class vt, class sh>
class DrawableTexturedEntity : public DrawableEntity<vt, sh>
{
protected:
	vector<ID3D11ShaderResourceView*> texture;
	XMFLOAT4X4 scale;
	XMFLOAT4X4 rot;
public:
	DrawableTexturedEntity(XMFLOAT3 pos, XMFLOAT3 rot, Model<vt> &model, sh &shader, ID3D11ShaderResourceView *texture = nullptr, XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f));
	DrawableTexturedEntity(DrawableTexturedEntity &&other);

	DrawableTexturedEntity(DrawableTexturedEntity&) = delete;
	DrawableTexturedEntity &operator=(DrawableTexturedEntity&) = delete;

	virtual void Render(const RenderParams &renderParams);
	virtual void Render(const RenderParams &renderParams, vector<ID3D11ShaderResourceView*> texture);
};

typedef DrawableTexturedEntity<TextureVertexType, TextureShader> SimpleTexturedEntity;

template<class vt, class sh>
DrawableTexturedEntity<vt, sh>::DrawableTexturedEntity(XMFLOAT3 pos, XMFLOAT3 rot, Model<vt> &model, sh &shader, ID3D11ShaderResourceView *texture, XMFLOAT3 scale)
: DrawableEntity(pos, model, shader)
{
	this->texture.push_back(texture);
	XMStoreFloat4x4(&this->scale, XMMatrixScaling(scale.x, scale.y, scale.z));
	XMStoreFloat4x4(&this->rot, XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z));
}

template<class vt, class sh>
DrawableTexturedEntity<vt, sh>::DrawableTexturedEntity(DrawableTexturedEntity &&other)
: DrawableEntity(move(other)), texture(move(other.texture)), scale(move(other.scale)), rot(move(other.rot))
{
}

template<class vt, class sh>
void DrawableTexturedEntity<vt, sh>::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	model.Set(params.context);
	XMMATRIX scale = XMLoadFloat4x4(&this->scale);
	XMMATRIX pos = XMLoadFloat4x4(&this->moveMatrix);
	XMMATRIX rot = XMLoadFloat4x4(&this->rot);
	XMMATRIX world = scale * rot * pos;
	shader.SetShaderParametersTextured(params, world, texture);
	shader.RenderShader(params.context, model.GetIndexCount());
}

template<class vt, class sh>
void DrawableTexturedEntity<vt, sh>::Render(const RenderParams &params, vector<ID3D11ShaderResourceView*> texture)
{
	this->texture = texture;
	Render(params);
}