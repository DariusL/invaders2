#include "BulletGraphics.h"


BulletGraphics::BulletGraphics(void)
{
}


BulletGraphics::~BulletGraphics(void)
{
	ShutdownBuffers();
}

void BulletGraphics::SetModel(Model *model)
{
	this->model = model;
}

bool BulletGraphics::Init(ID3D11Device* device, World *world, HWND handle)
{
	this->world = world;
	shader = unique_ptr<ColorInstancedShader>(new ColorInstancedShader());
	if(!shader->Init(device, handle))
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}

bool BulletGraphics::InitBuffers(ID3D11Device *device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexBuffers = new ID3D11Buffer*[2];

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = model->vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, vertexBuffers)))
		return false;

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = model->indices;
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

void BulletGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	Update(context);
	SetBuffers(context);
	shader->SetShaderParameters(context, transMatrix);
	shader->RenderShader(context, model->indexCount, bulletCount);
}

void BulletGraphics::SetBuffers(ID3D11DeviceContext *context)
{
	unsigned int strides[2];
	unsigned int offsets[2];

	strides[0] = sizeof(VertexType); 
	offsets[0] = 0;

	strides[1] = sizeof(D3DXVECTOR3);
	offsets[1] = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 2, vertexBuffers, strides, offsets);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void BulletGraphics::ShutdownBuffers()
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

void BulletGraphics::Update(ID3D11DeviceContext *context)
{
	list<Entity> bullets = world->GetBullets();

	bulletCount = bullets.size();

	D3DXVECTOR3 *bulletData = new D3DXVECTOR3[bulletCount];
	int i = 0;

	for(auto &x : bullets)
	{
		if(i >= MAX_BULLET_COUNT)
			break;
		bulletData[i] = x.GetPos();
		i++;
	}
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(vertexBuffers[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, bulletData, sizeof(D3DXVECTOR3) * bulletCount);

	context->Unmap(vertexBuffers[1], 0);
}