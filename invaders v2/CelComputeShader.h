#pragma once
#include "ComputeShader.h"
class CelComputeShader : public ComputeShader
{
protected:
	struct KernelBuffer
	{
		DirectX::XMFLOAT4X4 kernelX;
		DirectX::XMFLOAT4X4 kernelY;
	};

	struct OffsetBuffer
	{
		float offset;
		DirectX::XMFLOAT3 padding;
	};

	ComPtr<ID3D11Buffer> kernelBuffer;
	ComPtr<ID3D11Buffer> offsetBuffer;
public:
	CelComputeShader(wstring cs) :ComputeShader(cs){}
	virtual ~CelComputeShader(){}

	virtual void SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
};

