#include "includes.h"
#include "InstancedTextureShader.h"
#include "Globals.h"

void InstancedTextureShader::Init(ID3D11Device *device)
{
	IInstanceShader::Init(device);
	InitializeSampler(device);
}

vector<D3D11_INPUT_ELEMENT_DESC> InstancedTextureShader::GetInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC desc;
	vector<D3D11_INPUT_ELEMENT_DESC> ret;

	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	ret.push_back(desc);

	desc.SemanticName = "TEXCOORD";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	ret.push_back(desc);

	desc.SemanticName = "INSTANCE";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InputSlot = 1;
	desc.AlignedByteOffset = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	desc.InstanceDataStepRate = 1;

	ret.push_back(desc);

	for (unsigned int i = 1; i < 4; i++)
	{
		desc.SemanticIndex = i;
		desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

		ret.push_back(desc);
	}

	return ret;
}

void InstancedTextureShader::InitializeSampler(ID3D11Device *device)
{
	D3D11_SAMPLER_DESC samplerDesc;

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
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

	Assert(device->CreateSamplerState(&samplerDesc, &samplerState));
}

void InstancedTextureShader::SetShaderParametersInstancedTextured(const RenderParams &params, const vector<ID3D11ShaderResourceView*> &textures)
{
	IInstanceShader::SetShaderParametersInstanced(params);

	texturesSet = textures.size();
	for (unsigned int i = 0; i < texturesSet; i++)
		params.context->PSSetShaderResources(i, 1, &textures[i]);

	params.context->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

void InstancedTextureShader::RenderShaderInstanced(ID3D11DeviceContext *context, int indexCount, int instanceCount)
{
	IInstanceShader::RenderShaderInstanced(context, indexCount, instanceCount);
	for (unsigned int i = 0; i < texturesSet; i++)
		context->PSSetShaderResources(i, 1, nullResourceView.GetAddressOf());
}