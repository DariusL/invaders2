#include "includes.h"
#include "WaterShader.h"
#include "Utils.h"

void WaterShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	MirrorShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC cameraDesc, waterDesc;

	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.ByteWidth = sizeof(XMFLOAT4);
	cameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraDesc.MiscFlags = 0;
	cameraDesc.StructureByteStride = 0;
	cameraDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&cameraDesc, NULL, &cameraBuffer));

	waterDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	waterDesc.ByteWidth = sizeof(WaterType);
	waterDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	waterDesc.MiscFlags = 0;
	waterDesc.StructureByteStride = 0;
	waterDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&waterDesc, NULL, &waterBuffer));
}

void WaterShader::InitializeSampler(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeSampler(device);
	D3D11_SAMPLER_DESC samplerDesc;

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.MinLOD = 0;
	samplerDesc.MipLODBias = 0;

	Assert(device->CreateSamplerState(&samplerDesc, &waterSamplerState));
}

void WaterShader::SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	MirrorShader::SetShaderParametersTextured(params, world, textures);

	ComPtr<ID3D11DeviceContext> con = params.context;

	WaterType water;
	water.scale = params.waterScale;
	water.waterTranslation = params.waterTranslation;
	Utils::CopyToBuffer(waterBuffer, water, con);

	Utils::CopyToBuffer(cameraBuffer, params.camera->GetPosition(), params.context);

	con->PSSetSamplers(1, 1, waterSamplerState.GetAddressOf());

	con->VSSetConstantBuffers(3, 1, cameraBuffer.GetAddressOf());
	con->PSSetConstantBuffers(0, 1, waterBuffer.GetAddressOf());
}