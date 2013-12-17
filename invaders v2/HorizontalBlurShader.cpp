#include "includes.h"
#include "HorizontalBlurShader.h"
#include "App.h"

void HorizontalBlurShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	BlurBuffer data;

	int width, height;
	App::Get()->GetScreenDims(width, height);
	float fwidth = 1.0f / width;
	data.offset = XMFLOAT4(-fwidth, 0.0f, fwidth, 0.0f);

	data.weight = XMFLOAT4(1.0f, 0.9f, 0.55f, 0.18f);

	float norm = data.weight.x + 2.0f * (data.weight.y * data.weight.z * data.weight.w);

	data.weight.x /= norm;
	data.weight.y /= norm;
	data.weight.z /= norm;
	data.weight.w /= norm;

	resource.pSysMem = &data;
	resource.SysMemPitch = 0;
	resource.SysMemSlicePitch = 0;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(BlurBuffer);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	Assert(device->CreateBuffer(&desc, &resource, &blurBuffer));
}

void HorizontalBlurShader::InitializeSampler(ComPtr<ID3D11Device> device)
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

void HorizontalBlurShader::SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, world, textures);

	params.context->PSSetConstantBuffers(0, 1, blurBuffer.GetAddressOf());
}