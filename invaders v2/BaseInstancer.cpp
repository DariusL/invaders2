#include "BaseInstancer.h"

template<class Data>
BaseInstancer<Data>::BaseInstancer(shared_ptr<Model> model, int maxObjectCount)
{
	this->maxInstanceCount = maxObjectCount;
	this->model = model;
}

template<class Data>
BaseInstancer<Data>::~BaseInstancer(void)
{
}

template<class Data>
bool BaseInstancer<Data>::Init(ComPtr<ID3D11Device> device)
{
	shader = App::Get()->GetResourceManager()->GetColorInstancedShader();
	if(!InitBuffers(device))
		return false;
	return true;
}

template<class Data>
bool BaseInstancer<Data>::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	bulletData = unique_ptr<Data[]>(new Data[maxInstanceCount]);

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = &model->vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer)))
		return false;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(VertexType);

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = &model->indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer)))
		return false;

	ZeroMemory(&instanceBufferDesc, sizeof(instanceBufferDesc));
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(Data) * MAX_BULLET_COUNT;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	if(FAILED(device->CreateBuffer(&instanceBufferDesc, NULL, &instanceBuffer)))
		return false;

	instanceInfo.offset = 0;
	instanceInfo.stride = sizeof(Data);
	
	return true;
}

template<class Data>
void BaseInstancer<Data>::Render(RenderParams params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params);
	shader->RenderShader(params.context, model->indexCount, bulletCount);
}

template<class Data>
void BaseInstancer<Data>::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), &instanceInfo.stride, &instanceInfo.offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

template<class Data>
bool BaseInstancer<Data>::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(instanceCount == 0)
		return false;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, bulletData.get(), sizeof(Data) * bulletCount);

	context->Unmap(instanceBuffer.Get(), 0);

	return true;
}