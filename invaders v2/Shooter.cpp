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

bool Shooter::Init(ID3D11Device* device, HWND handle)
{
	shader = unique_ptr<ColorShader>(new ColorShader());
	if(!shader->Init(device, handle))
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}

bool Shooter::InitBuffers(ID3D11Device *device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, matrixBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, constantData;
	ID3D11Buffer *tVertex, *tIndex, *tMatrix;

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

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	constantData.pSysMem = &moveMatrix;
	constantData.SysMemPitch = 0;
	constantData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&matrixBufferDesc, &constantData, &tMatrix)))
		return false;
	matrixBuffer = unique_ptr<ID3D11Buffer, COMDeleter>(tMatrix);

	return true;
}

void Shooter::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	if(!Update(context))
		return;
	SetBuffers(context);
	shader->SetShaderParameters(context, transMatrix);
	shader->RenderShader(context, model->indexCount);
}

void Shooter::SetBuffers(ID3D11DeviceContext *context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType); 
	offset = 0;
    
	ID3D11Buffer *tVertex, *tMatrix;
	tVertex = vertexBuffer.get();
	tMatrix = matrixBuffer.get();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, &tVertex, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

	//Set object position buffer
	context->VSSetConstantBuffers(1, 1, &tMatrix);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Shooter::Update(ID3D11DeviceContext *context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(matrixBuffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, &moveMatrix, sizeof(moveMatrix));

	context->Unmap(matrixBuffer.get(), 0);

	return true;
}