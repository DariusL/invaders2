#include "Bullets.h"
#include "App.h"
#include "ResourceManager.h"


Bullets::Bullets(shared_ptr<Model> model)
{
	this->model = model;
}

Bullets::Bullets()
{
	this->model = App::Get()->GetResourceManager()->GetModel(ResourceManager::Models::MODEL_BULLET);
}


Bullets::~Bullets(void)
{
}

bool Bullets::Init(ID3D11Device* device)
{
	shader = unique_ptr<ColorInstancedShader>(new ColorInstancedShader());
	if(!shader->Init(device))
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}

bool Bullets::InitBuffers(ID3D11Device *device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	bulletData = unique_ptr<D3DXVECTOR3[]>(new D3DXVECTOR3[MAX_BULLET_COUNT]);

	vertexBuffers = new ID3D11Buffer*[2];

	strides = unique_ptr<unsigned int[]>(new unsigned int[2]);
	offsets = unique_ptr<unsigned int[]>(new unsigned int[2]);

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = model->vertices.get();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, vertexBuffers)))
		return false;

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = model->indices.get();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer)))
		return false;

	ZeroMemory(&instanceBufferDesc, sizeof(instanceBufferDesc));
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(D3DXVECTOR3) * MAX_BULLET_COUNT;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	if(FAILED(device->CreateBuffer(&instanceBufferDesc, NULL, vertexBuffers + 1)))
		return false;
	
	return true;
}

void Bullets::Render(RenderParams params)
{
	Update(params.context);
	SetBuffers(params.context);
	shader->SetShaderParameters(params);
	shader->RenderShader(params.context, model->indexCount, bulletCount);
}

void Bullets::SetBuffers(ID3D11DeviceContext *context)
{
	strides[0] = sizeof(VertexType); 
	offsets[0] = 0;

	strides[1] = sizeof(D3DXVECTOR3);
	offsets[1] = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 2, vertexBuffers, strides.get(), offsets.get());

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Bullets::ShutdownBuffers()
{
	// Release the index buffer.
	if(indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = NULL;
	}

	for(int i = 0; i < 2; i++)
	{
		vertexBuffers[i]->Release();
		vertexBuffers[i] = NULL;
	}
}

void Bullets::setBullets(const list<Entity> &bullets)
{
	bulletCount = bullets.size();

	int i = 0;

	for(auto &x : bullets)
	{
		if(i >= MAX_BULLET_COUNT)
			break;
		bulletData[i] = x.GetPos();
		i++;
	}
}

bool Bullets::Update(ID3D11DeviceContext *context)
{
	if(bulletCount == 0)
		return false;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(vertexBuffers[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, bulletData.get(), sizeof(D3DXVECTOR3) * bulletCount);

	context->Unmap(vertexBuffers[1], 0);

	return true;
}