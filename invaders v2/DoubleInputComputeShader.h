#pragma once
#include "ComputeShader.h"
class DoubleInputComputeShader : public ComputeShader
{
public:
	DoubleInputComputeShader(wstring cs) : ComputeShader(cs){}
	virtual ~DoubleInputComputeShader(){}

	virtual void SetShaderParameters(ComPtr<ID3D11DeviceContext> context, 
		ComPtr<ID3D11ShaderResourceView> input1, ComPtr <ID3D11ShaderResourceView> input2, ComPtr<ID3D11UnorderedAccessView> output);
	virtual void Start(ComPtr<ID3D11DeviceContext> context, uint width, uint height);
};

