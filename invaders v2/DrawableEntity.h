#pragma once
#include "entity.h"
#include "IDrawableObject.h"
#include "Model.h"
#include "includes.h"
#include "GlobalDiffuseShader.h"
#include "Utils.h"

class DrawableEntity : public Entity, public IDrawableObject
{
protected:
	ColorModel &model;
	XMFLOAT4X4 moveMatrix;
	GlobalDiffuseShader &shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float speed = 0.0f);
	DrawableEntity(DrawableEntity &&other);
	virtual ~DrawableEntity(void);

	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void Render(const RenderParams &renderParams);
protected:
	virtual void InitBuffers(ComPtr<ID3D11Device> device);
	virtual void SetBuffers(ComPtr<ID3D11DeviceContext> context);
	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
};

DrawableEntity::DrawableEntity(XMFLOAT3 pos, Model<vt> &model, sh &shader, float speed)
: Entity(pos, model.hitbox, speed), model(model), shader(shader)
{
}

 
DrawableEntity::DrawableEntity(DrawableEntity &&other)
: IDrawableObject(forward<DrawableEntity>(other)), Entity(forward<DrawableEntity>(other)),
model(move(other.model)), shader(move(other.shader)),
vertexBuffer(move(other.vertexBuffer)), indexBuffer(move(other.indexBuffer)),
moveMatrix(move(other.moveMatrix)), vertexInfo(move(other.vertexInfo))
{
}


void DrawableEntity::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(vt);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(vt)* model.vertices.size();
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	vertexData.pSysMem = model.vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(int)* model.indices.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	indexData.pSysMem = model.indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));
}

 
DrawableEntity::~DrawableEntity(void)
{
}

 
void DrawableEntity::Init(ComPtr<ID3D11Device> device)
{
	InitBuffers(device);
}

 
void DrawableEntity::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

 
void DrawableEntity::Render(const RenderParams &params)
{
	if (!Update(params.context))
		return;
	SetBuffers(params.context);
	XMMATRIX world = XMLoadFloat4x4(&moveMatrix);
	shader.SetShaderParameters(params, world);
	shader.RenderShader(params.context, model.indices.size());
}

 
bool DrawableEntity::Update(ComPtr<ID3D11DeviceContext> context)
{
	if (dead)
		return false;

	XMStoreFloat4x4(&moveMatrix, XMMatrixTranslation(pos.x, pos.y, pos.z));

	return true;
}