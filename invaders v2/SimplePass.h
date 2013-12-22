#pragma once
#include "IPass.h"
#include "CelComputeShader.h"
#include "DownSampleComputeShader.h"
#include "UpSampleComputeShader.h"
#include "HorizontalBlurComputeShader.h"
#include "VerticalBlurComputeShader.h"
#include "FilterDownSampleShader.h"

template<class sh>
class SimplePass : IPass
{
	sh &shader;
	uint width, height;
public:
	SimplePass(sh &shader, uint width, uint height);
	virtual ~SimplePass(){}

	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
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
typedef SimplePass<HorizontalBlurComputeShader> HorizontalBlurPass;
typedef SimplePass<VerticalBlurComputeShader> VerticalBlurPass;
typedef SimplePass<FilterDownSampleShader> FilterDownSamplePass;