#include "includes.h"
#include "WaterPlane.h"
#include "Utils.h"

WaterPlane::WaterPlane(D3DXVECTOR3 pos, TexturedModel &model, WaterShader &shader)
	:Entity(pos), shader(shader), model(model)
{
}

WaterPlane::~WaterPlane(void)
{
}

void WaterPlane::Init(ComPtr<ID3D11Device> device)
{
	for(int i = 0; i < 3; i++)
		textures.push_back(nullResource);
	InitBuffers(device);
	renderTarget = make_shared<RenderTarget>((int)model.hitbox.x, (int)model.hitbox.y);
	renderTarget->Init(device);

	Assert(D3DX11CreateShaderResourceViewFromFile(device.Get(), L"wave.dds", NULL, NULL, &textures[2], NULL));
}

void WaterPlane::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(TextureVertexType);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertexType) * model.vertices.size();
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	vertexData.pSysMem = model.vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(int) * model.indices.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	indexData.pSysMem = model.indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));
}

void WaterPlane::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void WaterPlane::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	textures[0] = renderTarget->GetRenderedTexture();
	SetBuffers(params.context);
	shader.SetShaderParametersTextured(params, moveMatrix, textures);
	shader.RenderShader(params.context, model.indices.size());
}

bool WaterPlane::Update(ComPtr<ID3D11DeviceContext> context)
{
	if(dead)
		return false;

	D3DXMatrixTranslation(&moveMatrix, pos.x, pos.y, pos.z);

	return true;
}