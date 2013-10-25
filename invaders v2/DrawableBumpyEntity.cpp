#include "includes.h"
#include "DrawableBumpyEntity.h"
#include "App.h"
#include "ResourceManager.h"
#include "Utils.h"

DrawableBumpyEntity::DrawableBumpyEntity(D3DXVECTOR3 pos, shared_ptr<TexturedNormalModel> model) : Entity(pos, model->hitbox)
{
	this->model = model;
}


DrawableBumpyEntity::~DrawableBumpyEntity(void)
{
}

bool DrawableBumpyEntity::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	shader = static_pointer_cast<NormalMappedShader, IShader>(rm->GetShader(ResourceManager::Shaders::NORMAL_MAPPED));
	if(!InitBuffers(device))
		return false;

	Assert(D3DX11CreateShaderResourceViewFromFile(device.Get(), L"stage7.dds", NULL, NULL, &normalMap, NULL));

	return true;
}

bool DrawableBumpyEntity::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(NormalMappedVertexType);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(NormalMappedVertexType) * model->vertices.size();
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

void DrawableBumpyEntity::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DrawableBumpyEntity::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix, normalMap);
	shader->RenderShader(params.context, model->indices.size());
}

bool DrawableBumpyEntity::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}