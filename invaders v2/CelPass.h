#pragma once
#include "includes.h"
#include "CelComputeShader.h"
using namespace Microsoft::WRL;
class CelPass
{
	CelComputeShader &shader;
	uint width, height;
public:
	CelPass(CelComputeShader &shader, uint width, uint height);
	~CelPass();

	void Init(ComPtr<ID3D11Device> device);
	void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
};

