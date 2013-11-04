#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "GlobalDiffuseShader.h"
#include "models.h"
#include "includes.h"
#include "Utils.h"

template<class vt>
class DrawableEntity : public Entity, public IDrawableObject
{
	shared_ptr<Model<vt>> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<IPositionShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	DrawableEntity(D3DXVECTOR3 pos, shared_ptr<Model<vt>> model, shared_ptr<IShader> shader);
	~DrawableEntity(void);

	bool Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &renderParams);
private:
	bool InitBuffers(ComPtr<ID3D11Device> device);
	void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	bool Update(ComPtr<ID3D11DeviceContext> context);
};

template<class vt>
bool DrawableEntity<vt>::InitBuffers(ComPtr<ID3D11Device> device)
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

template<class vt>
DrawableEntity<vt>::DrawableEntity(D3DXVECTOR3 pos, shared_ptr<Model<vt>> model, shared_ptr<IShader> shader) : Entity(pos, model->hitbox)
{
	this->model = model;
	this->shader = static_pointer_cast<IPositionShader, IShader>(shader);
}

template<class vt>
DrawableEntity<vt>::~DrawableEntity(void)
{
}

template<class vt>
bool DrawableEntity<vt>::Init(ComPtr<ID3D11Device> device)
{
	if(!InitBuffers(device))
		return false;
	return true;
}

template<class vt>
void DrawableEntity<vt>::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

template<class vt>
void DrawableEntity<vt>::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix);
	shader->RenderShader(params.context, model->indices.size());
}

template<class vt>
bool DrawableEntity<vt>::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}