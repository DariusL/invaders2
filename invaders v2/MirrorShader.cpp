#include "includes.h"
#include "MirrorShader.h"
#include "Utils.h"

void MirrorShader::SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, const ComVector<ID3D11ShaderResourceView> &textures)
{
	MatrixType matrixData;

	D3DXMatrixTranspose(&matrixData.view, &params.view);
	D3DXMatrixTranspose(&matrixData.projection, &params.projection);
	D3DXMatrixTranspose(&matrixData.world, &posMatrix);

	Utils::CopyToBuffer(matrixBuffer, matrixData, params.context);

	params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

	params.context->IASetInputLayout(layout.Get());

	params.context->PSSetShaderResources(0, 1, textures[0].GetAddressOf());

	params.context->VSSetShader(vertexShader.Get(), NULL, 0);
	params.context->PSSetShader(pixelShader.Get(), NULL, 0);

	params.context->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	D3DXMATRIX reflection;
	D3DXMatrixTranspose(&reflection, &params.reflecMatrix);

	Utils::CopyToBuffer(reflectionBuffer, reflection, params.context);

	params.context->VSSetConstantBuffers(1, 1, reflectionBuffer.GetAddressOf());
}

void MirrorShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));

	D3D11_BUFFER_DESC reflectionDesc;

	reflectionDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	reflectionDesc.ByteWidth = sizeof(D3DXMATRIX);
	reflectionDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	reflectionDesc.MiscFlags = 0;
	reflectionDesc.StructureByteStride = 0;
	reflectionDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&reflectionDesc, NULL, &reflectionBuffer));
}