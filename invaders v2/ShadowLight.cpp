#include "includes.h"
#include "ShadowLight.h"

ShadowLight::ShadowLight(XMFLOAT3 pos, XMFLOAT4 color, ColorModel &model, ColorShader &shader, int width, int height)
:Light(pos, color, model, shader), width(width), height(height)
{
	XMStoreFloat4x4(&view, XMMatrixLookToLH(XMLoadFloat3(&pos), XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)));
	XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.1f, 10000.0f));

	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
}

void ShadowLight::Prepare(RenderParams &params)
{
	params.pass = PASS_TYPE_NORMAL;
	params.lightView = params.view = GetViewMatrix();
	params.lightProject = params.projection = GetProjectionMatrix();
	params.lightPos = GetPos();
	params.clipPlane = ZeroVec4;
	SetRenderTarget(params.context);
	ClearTarget(params.context);
}

void ShadowLight::Init(ComPtr<ID3D11Device> device)
{
	Light::Init(device);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = (UINT)width;
	depthBufferDesc.Height = (UINT)height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	Assert(device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer));

	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	Assert(device->CreateShaderResourceView(depthStencilBuffer.Get(), &shaderResourceViewDesc, &shaderResourceView));

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &depthStencilView));

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	depthBufferDesc.Height = (UINT)height;
	depthBufferDesc.Width = (UINT)width;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.MiscFlags = 0;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	Assert(device->CreateTexture2D(&depthBufferDesc, nullptr, &renderTargetTexure));

	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	shaderResourceViewDesc.Format = depthBufferDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	Assert(device->CreateShaderResourceView(renderTargetTexure.Get(), &shaderResourceViewDesc, &renderTargetTextureView));

	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	renderTargetViewDesc.Format = depthBufferDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateRenderTargetView(renderTargetTexure.Get(), &renderTargetViewDesc, &renderTargetView));
}

void ShadowLight::SetRenderTarget(ComPtr<ID3D11DeviceContext> context)
{
	context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	context->RSSetViewports(1, &viewport);
}

void ShadowLight::ClearTarget(ComPtr<ID3D11DeviceContext> context)
{
	XMFLOAT4 color(0.0f, 0.0f, 0.0f, 1.0f);
	context->ClearRenderTargetView(renderTargetView.Get(), reinterpret_cast<float*>(&color));
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}