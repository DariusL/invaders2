#include "includes.h"
#include "RenderTarget.h"
#include "Utils.h"

RenderTarget::RenderTarget(int width, int height)
:width(width), height(height)
{

	clear[0] = 0.0f;
	clear[1] = 0.0f;
	clear[2] = 0.8f;
	clear[3] = 1.0f;

	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
}

RenderTarget::RenderTarget(RenderTarget &&other)
:width(other.width), height(other.height), renderTargetTexture(other.renderTargetTexture),
renderTargetView(other.renderTargetView), depthStencilBuffer(other.depthStencilBuffer),
depthStencilState(other.depthStencilState), depthStencilView(other.depthStencilView),
shaderResourceView(other.shaderResourceView), viewport(other.viewport)
{
	memcpy(&clear, &other.clear, sizeof(float)* 4);
} 

RenderTarget::~RenderTarget(void)
{
}

void RenderTarget::Init(ComPtr<ID3D11Device> device)
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
	textureDesc.Height = (UINT)height;
	textureDesc.Width = (UINT)width;
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

	depthBufferDesc.Width = (UINT)width;
	depthBufferDesc.Height = (UINT)height;
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

void RenderTarget::SetRenderTarget(ComPtr<ID3D11DeviceContext> context)
{
	context->OMSetDepthStencilState(depthStencilState.Get(), 1);
	context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	context->RSSetViewports(1, &viewport);
}

void RenderTarget::ClearTarget(ComPtr<ID3D11DeviceContext> context)
{
	context->ClearRenderTargetView(renderTargetView.Get(), clear);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}