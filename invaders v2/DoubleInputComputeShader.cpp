#include "includes.h"
#include "DoubleInputComputeShader.h"

void DoubleInputComputeShader::SetShaderParameters(ComPtr<ID3D11DeviceContext> context,
	ComPtr<ID3D11ShaderResourceView> input1, ComPtr <ID3D11ShaderResourceView> input2, ComPtr<ID3D11UnorderedAccessView> output)
{
	ComputeShader::SetShaderParameters(context, input1, output);
	context->CSSetShaderResources(1, 1, input2.GetAddressOf());
}

void DoubleInputComputeShader::Start(ComPtr<ID3D11DeviceContext> context, uint width, uint height)
{
	ComputeShader::Start(context, width, height);
	context->CSSetShaderResources(1, 1, nullResourceView.GetAddressOf());
}