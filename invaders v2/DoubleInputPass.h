#pragma once
#include "TexelSumComputeShader.h"

template<class sh>
class DoubleInputPass
{
	sh &shader;
	uint width, height;
public:
	DoubleInputPass(sh &shader, uint width, uint height);
	virtual ~DoubleInputPass(){}

	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input1, 
		ComPtr<ID3D11ShaderResourceView> input2, ComPtr<ID3D11UnorderedAccessView> output);
};

template<class sh>
DoubleInputPass<sh>::DoubleInputPass(sh &shader, uint width, uint height)
:shader(shader), width(width), height(height)
{
}

template<class sh>
void DoubleInputPass<sh>::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input1,
	ComPtr<ID3D11ShaderResourceView> input2, ComPtr<ID3D11UnorderedAccessView> output)
{
	shader.SetShaderParameters(context, input1, input2, output);
	shader.Start(context, width, height);
}

typedef DoubleInputPass<TexelSumComputeShader> TexelSumPass;