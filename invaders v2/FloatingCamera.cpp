#include "includes.h"
#include "FloatingCamera.h"
#include "ResourceManager.h"
#include "App.h"


FloatingCamera::FloatingCamera(D3DXVECTOR2 viewportSize, D3DXVECTOR2 screenPos)
{
	this->viewportSize = viewportSize;
	this->screenPos = screenPos;
}


FloatingCamera::~FloatingCamera(void)
{
}

bool FloatingCamera::Init(ComPtr<ID3D11Device> device)
{
	ResourceManager *rm = App::Get()->GetResourceManager();
	shader = static_pointer_cast<ITextureShader, IShader>(rm->GetShader(ResourceManager::Shaders::TEXTURE));
	if(!InitBuffers(device))
		return false;
	return true;
}

bool FloatingCamera::InitBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vector<TextureVertexType> vertices;
	vector<int> indices;

	TextureVertexType vertex;
	
	vertex.position = D3DXVECTOR3(-0.5f * viewportSize.x, -0.5f * viewportSize.y, 0.0f);  // Bottom left.
	vertex.tex = D3DXVECTOR2(0.0f, 1.0f);
	vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-0.5f * viewportSize.x, 0.5f * viewportSize.y, 0.0f);  // Top left
	vertex.tex = D3DXVECTOR2(0.0f, 0.0f);
	vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.5f * viewportSize.x, -0.5f * viewportSize.y, 0.0f);  // Bottom right.
	vertex.tex = D3DXVECTOR2(1.0f, 1.0f);
	vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.5f * viewportSize.x, 0.5f * viewportSize.y, 0.0f);  // Top right.
	vertex.tex = D3DXVECTOR2(1.0f, 0.0f);
	vertices.push_back(vertex);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	vertexInfo.offset = 0;
	vertexInfo.stride = sizeof(NormalVertexType);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertices.size();
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	vertexData.pSysMem = &vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer));

	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(int) * indices.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Assert(device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer));

	return true;
}

void FloatingCamera::InitRenderTarget(ComPtr<ID3D11Device> device)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.Height = viewportSize.y;
	textureDesc.Width = viewportSize.x;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;

	Assert(device->CreateTexture2D(&textureDesc, NULL, &renderTargetTexture));

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateRenderTargetView(renderTargetTexture.Get(), &renderTargetViewDesc, &renderTargetView));

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	Assert(device->CreateShaderResourceView(renderTargetTexture.Get(), &shaderResourceViewDesc, &shaderResourceView));
}

void FloatingCamera::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void FloatingCamera::Render(RenderParams params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix, shaderResourceView);
	shader->RenderShader(params.context, 6);
}

bool FloatingCamera::Update(ComPtr<ID3D11DeviceContext> context)
{
	D3DXMatrixTranslation(&moveMatrix, screenPos.x, screenPos.y, 0);

	return true;
}