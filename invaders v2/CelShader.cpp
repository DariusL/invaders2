#include "includes.h"
#include "CelShader.h"
#include "App.h"

#define SOBEL 0
#define SCHARR 1

#define KERNEL SOBEL

void CelShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	KernelBuffer kernelData;
	OffsetBuffer offsetData;

	//such c++
#if KERNEL == SOBEL
	offsetData.offset = 0.2f;
	kernelData.kernelX = XMFLOAT4X4(1, 0, -1, 0, 2, 0, -2, 0, 1, 0, -1, 0, 0, 0, 0, 0);
#else
	offsetData.offset = -0.2f;
	kernelData.kernelX = XMFLOAT4X4(3, 10, 3, 0, 0, 0, 0, 0, -3, -10, -3, 0, 0, 0, 0, 0);
#endif
	//much RAII	
	XMStoreFloat4x4(&kernelData.kernelY, XMMatrixTranspose(XMLoadFloat4x4(&kernelData.kernelX)));

	int width, height;
	App::Get()->GetScreenDims(width, height);
	float fwidth = 1.0f / width;
	float fheight = 1.0f / height;
	offsetData.xOffset = XMFLOAT3(-fwidth, 0.0f, fwidth);
	offsetData.yOffset = XMFLOAT3(-fheight, 0.0f, fheight);

	resource.pSysMem = &kernelData;
	resource.SysMemPitch = 0;
	resource.SysMemSlicePitch = 0;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(KernelBuffer);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	Assert(device->CreateBuffer(&desc, &resource, &kernelBuffer));

	desc.ByteWidth = sizeof(OffsetBuffer);
	resource.pSysMem = &offsetData;

	Assert(device->CreateBuffer(&desc, &resource, &offsetBuffer));
}

void CelShader::InitializeSampler(ComPtr<ID3D11Device> device)
{
	D3D11_SAMPLER_DESC samplerDesc;

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.MinLOD = 0;
	samplerDesc.MipLODBias = 0;

	Assert(device->CreateSamplerState(&samplerDesc, &samplerState));
}

void CelShader::SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, world, textures);

	params.context->PSSetConstantBuffers(0, 1, kernelBuffer.GetAddressOf());
	params.context->PSSetConstantBuffers(1, 1, offsetBuffer.GetAddressOf());
}