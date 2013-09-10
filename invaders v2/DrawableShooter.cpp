#include "DrawableShooter.h"
#include "App.h"
#include "ResourceManager.h"

DrawableShooter::~DrawableShooter(void)
{
}

DrawableShooter::DrawableShooter(float speed, float fireRate, shared_ptr<Model> model): Shooter(model->hitbox, speed, fireRate)
{
	this->model = model;
}

bool DrawableShooter::Init(ComPtr<ID3D11Device> device)
{
	shader = static_pointer_cast<ColorShader, IShader>(App::Get()->GetResourceManager()->GetShader(ResourceManager::Shaders::COLOR));
	if(shader == NULL)
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}

bool DrawableShooter::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = &model->vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(VertexType);

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = &model->indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));

	return true;
}

void DrawableShooter::Render(RenderParams params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix);
	shader->RenderShader(params.context, model->indexCount);
}

void DrawableShooter::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool DrawableShooter::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}