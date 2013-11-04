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
	clear[0] = 0.0f;
	clear[1] = 0.0f;
	clear[2] = 0.0f;
	clear[3] = 1.0f;

	viewport.Width = viewportSize.x;
	viewport.Height = viewportSize.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	ResourceManager *rm = App::Get()->GetResourceManager();
	shader = rm->GetShader<ITextureShader>();
	if(!InitBuffers(device))
		return false;

	InitRenderTarget(device);

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
	vertexInfo.stride = sizeof(TextureVertexType);

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertexType) * vertices.size();
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
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.Height = (UINT)viewportSize.y;
	textureDesc.Width = (UINT)viewportSize.x;
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

	depthBufferDesc.Width = (UINT)viewportSize.x;
	depthBufferDesc.Height = (UINT)viewportSize.y;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	Assert(device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer));

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Assert(device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState));

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &depthStencilView));
}

void FloatingCamera::SetBuffers(ComPtr<ID3D11DeviceContext> context)
{
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vertexInfo.stride, &vertexInfo.offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void FloatingCamera::Render(const RenderParams &params)
{
	if(!Update(params.context))
		return;
	SetBuffers(params.context);
	shader->SetShaderParameters(params, moveMatrix, shaderResourceView);
	shader->RenderShader(params.context, 6);
}

bool FloatingCamera::Update(ComPtr<ID3D11DeviceContext> context)
{
	D3DXMatrixTranslation(&moveMatrix, screenPos.x, screenPos.y, 1.0f);

	return true;
}

void FloatingCamera::SetRenderTarget(ComPtr<ID3D11DeviceContext> context)
{
	context->OMSetDepthStencilState(depthStencilState.Get(), 1);
	context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	context->RSSetViewports(1, &viewport);
}

void FloatingCamera::ClearTarget(ComPtr<ID3D11DeviceContext> context)
{
	context->ClearRenderTargetView(renderTargetView.Get(), clear);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}