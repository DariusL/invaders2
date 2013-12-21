#pragma once

#include "CelComputeShader.h"
#include "DownSampleComputeShader.h"
#include "UpSampleComputeShader.h"

template<class sh>
class SimplePass
{
	sh &shader;
	uint width, height;
public:
	SimplePass(sh &shader, uint width, uint height);
	virtual ~SimplePass(){}

	void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
};

template<class sh>
SimplePass<sh>::SimplePass(sh &shader, uint width, uint height)
:shader(shader), width(width), height(height)
{
}

template<class sh>
void SimplePass<sh>::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output)
{
	shader.SetShaderParameters(context, input, output);
	shader.Start(context, width, height);
}

typedef SimplePass<CelComputeShader> CelPass;
typedef SimplePass<UpSampleComputeShader> UpSamplePass;
typedef SimplePass<DownSampleComputeShader> DownSamplePass;