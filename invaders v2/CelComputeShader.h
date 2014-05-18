#pragma once
#include "ComputeShader.h"
class CelComputeShader : public ComputeShader
{
protected:
	struct KernelBuffer
	{
		e::XMFLOAT4X4 kernelX;
		e::XMFLOAT4X4 kernelY;
	};

	struct OffsetBuffer
	{
		float offset;
		e::XMFLOAT3 padding;
	};

	e::ComPtr<ID3D11Buffer> kernelBuffer;
	e::ComPtr<ID3D11Buffer> offsetBuffer;
public:
	CelComputeShader(e::wstring cs) :ComputeShader(cs){}
	virtual ~CelComputeShader(){}

	virtual void SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);
};

