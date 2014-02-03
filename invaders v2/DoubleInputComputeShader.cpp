#include "includes.h"
#include "DoubleInputComputeShader.h"

void DoubleInputComputeShader::SetShaderParameters(ID3D11DeviceContext *context,
	ID3D11ShaderResourceView *input1, ID3D11ShaderResourceView *input2, ID3D11UnorderedAccessView *output)
{
	ComputeShader::SetShaderParameters(context, input1, output);
	context->CSSetShaderResources(1, 1, &input2);
}

void DoubleInputComputeShader::Start(ID3D11DeviceContext *context, uint width, uint height)
{
	ComputeShader::Start(context, width, height);
	context->CSSetShaderResources(1, 1, nullResourceView.GetAddressOf());
}