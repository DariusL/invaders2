#pragma once
#include "IPass.h"
#include "CelComputeShader.h"
#include "DownSampleComputeShader.h"
#include "UpSampleComputeShader.h"
#include "HorizontalBlurComputeShader.h"
#include "VerticalBlurComputeShader.h"
#include "FilterDownSampleShader.h"
#include "CopyComputeShader.h"
#include "ResourceManager.h"

template<typename sh>
class SimplePass : IPass
{
	sh &shader;
	uint width, height;
public:
	SimplePass(uint width, uint height);
	virtual ~SimplePass(){}

	virtual void Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
};

template<class sh>
SimplePass<sh>::SimplePass(uint width, uint height)
:shader(RM::Get().GetShader<sh>()), width(width), height(height)
{
}

template<class sh>
void SimplePass<sh>::Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output)
{
	shader.SetShaderParameters(context, input, output);
	shader.Start(context, width, height);
}

using CelPass = SimplePass<CelComputeShader>;
using UpSamplePass = SimplePass<UpSampleComputeShader>;
using DownSamplePass = SimplePass<DownSampleComputeShader>;
using HorizontalBlurPass = SimplePass<HorizontalBlurComputeShader>;
using VerticalBlurPass = SimplePass<VerticalBlurComputeShader>;
using FilterDownSamplePass = SimplePass<FilterDownSampleShader>;
using CopyPass = SimplePass<CopyComputeShader>;