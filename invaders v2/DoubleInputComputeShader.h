#pragma once
#include "ComputeShader.h"
class DoubleInputComputeShader : public ComputeShader
{
public:
	DoubleInputComputeShader(wstring cs) : ComputeShader(cs){}
	virtual ~DoubleInputComputeShader(){}

	virtual void SetShaderParameters(ID3D11DeviceContext *context, 
		ID3D11ShaderResourceView *input1, ID3D11ShaderResourceView *input2, ID3D11UnorderedAccessView *output);
	virtual void Start(ID3D11DeviceContext *context, uint width, uint height);
};

