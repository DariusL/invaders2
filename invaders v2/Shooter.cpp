#include "Shooter.h"
#include "App.h"
#include "ResourceManager.h"

Shooter::Shooter(void)
{
}


Shooter::~Shooter(void)
{
}

Shooter::Shooter(D3DXVECTOR2 size, float speed, float fireRate, shared_ptr<Model> model)
{
	this->size = size;
	this->speed = speed;
	this->fireRate = fireRate;
	this->lastFired = 0;
	this->dead = false;
	this->model = model;
}

bool Shooter::Init(ID3D11Device* device)
{
	shader = App::Get()->GetResourceManager()->GetColorShader();
	if(!InitBuffers(device))
		return false;
	return true;
}

bool Shooter::InitBuffers(ID3D11Device *device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	ID3D11Buffer *tVertex, *tIndex;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = model->vertices.get();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &tVertex)))
		return false;
	vertexBuffer = unique_ptr<ID3D11Buffer, COMDeleter>(tVertex);

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = model->indices.get();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &tIndex)))
		return false;
	indexBuffer = unique_ptr<ID3D11Buffer, COMDeleter>(tIndex);

	return true;
}

void Shooter::Render(RenderParams params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix);
	shader->RenderShader(params.context, model->indexCount);
}

void Shooter::SetBuffers(ID3D11DeviceContext *context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType); 
	offset = 0;
    
	ID3D11Buffer *tVertex;
	tVertex = vertexBuffer.get();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, &tVertex, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Shooter::Update(ID3D11DeviceContext *context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}