#include "includes.h"
#include "MirrorShader.h"
#include "Utils.h"

void MirrorShader::SetShaderParametersTextured(const RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, world, textures);

	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranspose(params.reflecMatrix));

	Utils::CopyToBuffer(reflectionBuffer, matrix, params.context);

	params.context->VSSetConstantBuffers(2, 1, reflectionBuffer.GetAddressOf());
}

void MirrorShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC reflectionDesc;

	reflectionDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	reflectionDesc.ByteWidth = sizeof(XMMATRIX);
	reflectionDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	reflectionDesc.MiscFlags = 0;
	reflectionDesc.StructureByteStride = 0;
	reflectionDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&reflectionDesc, NULL, &reflectionBuffer));
}