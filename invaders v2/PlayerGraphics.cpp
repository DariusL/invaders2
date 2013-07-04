#include "PlayerGraphics.h"

PlayerGraphics::PlayerGraphics()
{

}

void PlayerGraphics::SetModel(Model model)
{
	this->model = model;
}

void PlayerGraphics::SetPos(D3DXVECTOR3 pos)
{
	this->pos = pos;
	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);
}

bool PlayerGraphics::Init(ID3D11Device* device, World *world, HWND handle)
{
	this->world = world;
	shader = new ColorShader();
	if(!shader->Init(device, handle))
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}

bool PlayerGraphics::InitBuffers(ID3D11Device *device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, matrixBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, constantData;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model.vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = model.vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer)))
		return false;

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model.indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = model.indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer)))
		return false;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	constantData.pSysMem = &moveMatrix;
	constantData.SysMemPitch = 0;
	constantData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&matrixBufferDesc, &constantData, &matrixBuffer)))
		return false;

	return true;
}

void PlayerGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	SetBuffers(context);
	shader->SetShaderParameters(context, transMatrix);
	shader->RenderShader(context, model.indexCount);
}

void PlayerGraphics::SetBuffers(ID3D11DeviceContext *context)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType); 
	offset = 0;

	Update(context);
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Set object position buffer
	context->VSSetConstantBuffers(1, 1, &matrixBuffer);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void PlayerGraphics::Shutdown()
{
	ShutdownBuffers();
	if(shader)
	{
		shader->Shutdown();
		delete shader;
		shader = NULL;
	}
	
	delete [] model.vertices;
	delete [] model.indices;
}

void PlayerGraphics::ShutdownBuffers()
{
	// Release the index buffer.
	if(indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = NULL;
	}

	if(vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}
}

void PlayerGraphics::Update(ID3D11DeviceContext *context)
{
	pos = world->GetPlayerPos();

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, &moveMatrix, sizeof(moveMatrix));

	context->Unmap(matrixBuffer, 0);
	
}