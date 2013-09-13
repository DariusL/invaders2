#include "BaseInstancer.h"
#include "App.h"


BaseInstancer::BaseInstancer(shared_ptr<Model> model, int maxObjectCount, int instanceSize)
{
	this->maxInstanceCount = maxObjectCount;
	this->model = model;
	this->instanceSize = instanceSize;
}


BaseInstancer::~BaseInstancer(void)
{
}


bool BaseInstancer::Init(ComPtr<ID3D11Device> device)
{
	shader = static_pointer_cast<ColorInstancedShader, IShader>(App::Get()->GetResourceManager()->GetShader(ResourceManager::Shaders::COLOR_INSTANCED));
	if(shader == NULL)
		return false;
	if(!InitBuffers(device))
		return false;
	return true;
}


bool BaseInstancer::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	instanceData = unique_ptr<byte[]>(new byte[maxInstanceCount * instanceSize]);

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * model->vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexData.pSysMem = &model->vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(VertexType);

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * model->indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	indexData.pSysMem = &model->indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));

	ZeroMemory(&instanceBufferDesc, sizeof(instanceBufferDesc));
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = instanceSize * maxInstanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	Assert(device->CreateBuffer(&instanceBufferDesc, NULL, &instanceBuffer));

	instanceInfo.offset = 0;
	instanceInfo.stride = instanceSize;
	
	return true;
}


void BaseInstancer::Render(RenderParams params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params);
	shader->RenderShader(params.context, model->indices.size(), instanceCount);
}


void BaseInstancer::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetVertexBuffers(1, 1, instanceBuffer.GetAddressOf(), &instanceInfo.stride, &instanceInfo.offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool BaseInstancer::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(instanceCount == 0)
		return false;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, instanceData.get(), instanceSize * instanceCount);

	context->Unmap(instanceBuffer.Get(), 0);

	return true;
}