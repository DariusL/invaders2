#pragma once

#include "includes.h"
#include "DrawableEntity.h"
#include "TextureShader.h"
#include "Model.h"

template<class vt, class sh>
class DrawableTexturedEntity : public DrawableEntity<vt, sh>
{
	ComVector<ID3D11ShaderResourceView> texture;
	D3DXMATRIX scale;
public:
	DrawableTexturedEntity(D3DXVECTOR3 pos, Model<vt> &model, sh &shader, ComPtr<ID3D11ShaderResourceView> texture = NULL, D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	DrawableTexturedEntity(DrawableTexturedEntity &&other);
	virtual ~DrawableTexturedEntity(void){}

	virtual void Render(const RenderParams &renderParams);
	virtual void Render(const RenderParams &renderParams, ComVector<ID3D11ShaderResourceView> texture);
};

typedef DrawableTexturedEntity<TextureVertexType, TextureShader> SimpleTexturedEntity;

template<class vt, class sh>
DrawableTexturedEntity<vt, sh>::DrawableTexturedEntity(D3DXVECTOR3 pos, Model<vt> &model, sh &shader, ComPtr<ID3D11ShaderResourceView> texture, D3DXVECTOR3 scale)
: DrawableEntity(pos, model, shader)
{
	this->texture.push_back(texture);
	D3DXMatrixScaling(&this->scale, scale.x, scale.y, scale.z);
}

template<class vt, class sh>
DrawableTexturedEntity<vt, sh>::DrawableTexturedEntity(DrawableTexturedEntity &&other)
: DrawableEntity(forward<DrawableTexturedEntity>(other)), texture(move(other.texture))
{
}

template<class vt, class sh>
void DrawableTexturedEntity<vt, sh>::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	SetBuffers(params.context);
	shader.SetShaderParametersTextured(params, scale * moveMatrix, texture);
	shader.RenderShader(params.context, model.indices.size());
}

template<class vt, class sh>
void DrawableTexturedEntity<vt, sh>::Render(const RenderParams &params, ComVector<ID3D11ShaderResourceView> texture)
{
	this->texture = texture;
	Render(params);
}