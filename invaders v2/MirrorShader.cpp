#include "includes.h"
#include "MirrorShader.h"
#include "Utils.h"

void MirrorShader::SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, posMatrix, textures);

	D3DXMATRIX reflection;
	D3DXMatrixTranspose(&reflection, &params.reflecMatrix);

	Utils::CopyToBuffer(reflectionBuffer, reflection, params.context);

	params.context->VSSetConstantBuffers(1, 1, reflectionBuffer.GetAddressOf());
}

void MirrorShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC reflectionDesc;

	reflectionDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	reflectionDesc.ByteWidth = sizeof(D3DXMATRIX);
	reflectionDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	reflectionDesc.MiscFlags = 0;
	reflectionDesc.StructureByteStride = 0;
	reflectionDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&reflectionDesc, NULL, &reflectionBuffer));
}