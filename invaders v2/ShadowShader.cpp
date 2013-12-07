#include "includes.h"
#include "ShadowShader.h"


void ShadowShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC desc;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(XMFLOAT4);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	Assert(device->CreateBuffer(&desc, NULL, &pixelLightBuffer));

	desc.ByteWidth = sizeof(ShadowLightBufferType);
	Assert(device->CreateBuffer(&desc, NULL, &vertexLightBuffer));

	desc.ByteWidth = sizeof(XMFLOAT4);
	Assert(device->CreateBuffer(&desc, NULL, &inverseMatrixBuffer));
}

void ShadowShader::InitializeSampler(ComPtr<ID3D11Device> device)
{
	D3D11_SAMPLER_DESC desc;

	desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_LESS;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	Assert(device->CreateSamplerState(&desc, &compareSamplerState));
}

vector<D3D11_INPUT_ELEMENT_DESC> ShadowShader::GetInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC desc;

	auto ret = TextureShader::GetInputLayout();

	desc.SemanticName = "NORMAL";
	desc.SemanticIndex = 0;
	desc.InputSlot = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	ret.push_back(desc);

	desc.SemanticName = "TEXCOORD";
	desc.SemanticIndex = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	ret.push_back(desc);

	desc.SemanticName = "TEXCOORD";
	desc.SemanticIndex = 2;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

	ret.push_back(desc);

	return ret;
}

void ShadowShader::SetShaderParametersTextured(const RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, world, textures);
	auto context = params.context;

	XMFLOAT4X4 inverseWorld;
	XMStoreFloat4x4(&inverseWorld, XMMatrixTranspose(XMMatrixInverse(NULL, world)));

	Utils::CopyToBuffer(inverseMatrixBuffer, inverseWorld, context);

	Utils::CopyToBuffer(pixelLightBuffer, params.diffuseColor, context);

	ShadowLightBufferType vertexLightData;
	vertexLightData.lightPos = params.lightPos;
	XMStoreFloat4x4(&vertexLightData.lightView, XMMatrixTranspose(params.lightView));
	XMStoreFloat4x4(&vertexLightData.lightProject, XMMatrixTranspose(params.lightProject));

	Utils::CopyToBuffer(vertexLightBuffer, vertexLightData, context);

	context->PSSetSamplers(1, 1, compareSamplerState.GetAddressOf());
	context->PSSetConstantBuffers(0, 1, pixelLightBuffer.GetAddressOf());
	context->VSSetConstantBuffers(2, 1, vertexLightBuffer.GetAddressOf());
	context->VSSetConstantBuffers(3, 1, inverseMatrixBuffer.GetAddressOf());
}