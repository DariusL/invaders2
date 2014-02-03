#pragma once
#include "ComputeShader.h"
class FilterDownSampleShader : public ComputeShader
{
public:
	FilterDownSampleShader(wstring cs) :ComputeShader(cs){}
	virtual ~FilterDownSampleShader(){}

	virtual void SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);

	ComPtr<ID3D11Buffer> filterBuffer;

	struct FilterBuffer
	{
		float luminance;
		float middleGray;
		float whiteCutoff;
		float padding;
	};
};