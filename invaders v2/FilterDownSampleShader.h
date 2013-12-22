#pragma once
#include "ComputeShader.h"
class FilterDownSampleShader : public ComputeShader
{
public:
	FilterDownSampleShader(wstring cs) :ComputeShader(cs){}
	virtual ~FilterDownSampleShader(){}

	virtual void SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> filterBuffer;

	struct FilterBuffer
	{
		float luminance;
		float middleGray;
		float whiteCutoff;
		float padding;
	};
};