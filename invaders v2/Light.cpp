#include "includes.h"
#include "Light.h"
#include "App.h"
#include "ResourceManager.h"

Light::Light(D3DXVECTOR3 pos, D3DXVECTOR4 color) : Entity(pos, D3DXVECTOR2(2.0f, 2.0f))
{
	this->model = App::Get()->GetResourceManager()->GetModel(ResourceManager::Models::MODEL_BALL);
	this->color = color;
}

Light::~Light(void)
{
}

void Light::SetPos(float pitch, float r)
{
	this->pitch = pitch;
	this->r = r;
}

D3DXVECTOR3 Light::GetPos()
{
	return D3DXVECTOR3(0.0f, r * sin(pitch), -r * cos(pitch));
}

bool Light::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	shader = static_pointer_cast<IPositionShader, IShader>(rm->GetShader(ResourceManager::Shaders::COLOR));
	if(!InitBuffers(device))
		return false;
	return true;
}

bool Light::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(VertexType);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertices.size();
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

void Light::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Light::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix);
	shader->RenderShader(params.context, model->indices.size());
}

bool Light::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;
	D3DXMATRIX rot;
	D3DXMatrixTranslation(&moveMatrix, 0.0f, 0.0f, -r);
	D3DXMatrixRotationX(&rot, pitch);
	moveMatrix *= rot;

	return true;
}