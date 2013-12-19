#include "includes.h"
#include "CelPass.h"
#include "Utils.h"

CelPass::CelPass(CelComputeShader &shader, uint width, uint height)
:shader(shader), width(width), height(height)
{
}


CelPass::~CelPass()
{
}

void CelPass::Init(ComPtr<ID3D11Device> device)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_UNORDERED_ACCESS_VIEW_DESC unorderedAccessViewDesc;

	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.Height = (UINT)height;
	textureDesc.Width = (UINT)width;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;

	Assert(device->CreateTexture2D(&textureDesc, NULL, &output));

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	Assert(device->CreateShaderResourceView(output.Get(), &shaderResourceViewDesc, &outputResourceView));

	unorderedAccessViewDesc.Format = textureDesc.Format;
	unorderedAccessViewDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	unorderedAccessViewDesc.Texture2D.MipSlice = 0;

	Assert(device->CreateUnorderedAccessView(output.Get(), &unorderedAccessViewDesc, &outputUnorderedView));
}

ComPtr<ID3D11ShaderResourceView> CelPass::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> texture)
{
	shader.SetShaderParameters(context, texture, outputUnorderedView);
	shader.Start(context, width, height);
	return outputResourceView;
}