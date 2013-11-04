#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "GlobalDiffuseShader.h"
#include "models.h"
#include "includes.h"
#include "Utils.h"

template<class vt, class sh>
class DrawableEntity : public Entity, public IDrawableObject
{
protected:
	shared_ptr<Model<vt>> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<sh> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	DrawableEntity(D3DXVECTOR3 pos, shared_ptr<Model<vt>> model, shared_ptr<sh> shader);
	virtual ~DrawableEntity(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	virtual void Render(const RenderParams &renderParams);
protected:
	virtual bool InitBuffers(ComPtr<ID3D11Device> device);
	virtual void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
};

template<class vt, class sh>
bool DrawableEntity<vt, sh>::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(vt);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(vt) * model->vertices.size();
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	vertexData.pSysMem = &model->vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indices.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	indexData.pSysMem = &model->indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));

	return true;
}

template<class vt, class sh>
DrawableEntity<vt, sh>::DrawableEntity(D3DXVECTOR3 pos, shared_ptr<Model<vt>> model, shared_ptr<sh> shader) : Entity(pos, model->hitbox)
{
	this->model = model;
	this->shader = shader;
}

template<class vt, class sh>
DrawableEntity<vt, sh>::~DrawableEntity(void)
{
}

template<class vt, class sh>
bool DrawableEntity<vt, sh>::Init(ComPtr<ID3D11Device> device)
{
	if(!InitBuffers(device))
		return false;
	return true;
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

template<class vt, class sh>
void DrawableEntity<vt, sh>::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix);
	shader->RenderShader(params.context, model->indices.size());
}

template<class vt, class sh>
bool DrawableEntity<vt, sh>::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}