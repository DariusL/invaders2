#include "includes.h"
#include "TextureShader.h"
#include "Utils.h"

vector<D3D11_INPUT_ELEMENT_DESC> TextureShader::GetInputLayout()
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

	return ret;
}

void TextureShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));
}

void TextureShader::InitializeSampler(ComPtr<ID3D11Device> device)
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

void TextureShader::SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX moveMatrix, const ComVector<ID3D11ShaderResourceView> &textures)
{
	D3DXMATRIX transform;

	transform = moveMatrix * params.transMatrix;
	D3DXMatrixTranspose(&transform, &transform);
	Utils::CopyToBuffer(matrixBuffer, transform, params.context);

	params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

	params.context->IASetInputLayout(layout.Get());

	params.context->PSSetShaderResources(0, 1, textures[0].GetAddressOf());

	params.context->VSSetShader(vertexShader.Get(), NULL, 0);
	params.context->PSSetShader(pixelShader.Get(), NULL, 0);

	params.context->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

void TextureShader::RenderShader(ComPtr<ID3D11DeviceContext> deviceContext, int indexCount)
{
	deviceContext->DrawIndexed(indexCount, 0, 0);
	deviceContext->PSSetShaderResources(0, 1, nullResource.GetAddressOf());
 }