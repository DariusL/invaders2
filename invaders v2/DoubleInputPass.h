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

	virtual void Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input1, 
		ID3D11ShaderResourceView *input2, ID3D11UnorderedAccessView *output);
};

template<class sh>
DoubleInputPass<sh>::DoubleInputPass(sh &shader, uint width, uint height)
:shader(shader), width(width), height(height)
{
}

template<class sh>
void DoubleInputPass<sh>::Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input1,
	ID3D11ShaderResourceView *input2, ID3D11UnorderedAccessView *output)
{
	shader.SetShaderParameters(context, input1, input2, output);
	shader.Start(context, width, height);
}

typedef DoubleInputPass<TexelSumComputeShader> TexelSumPass;