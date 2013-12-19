#pragma once
#include "includes.h"
#include "CelComputeShader.h"
using namespace Microsoft::WRL;
class CelPass
{
	ComPtr<ID3D11Texture2D> output;
	ComPtr<ID3D11ShaderResourceView> outputResourceView;
	ComPtr<ID3D11UnorderedAccessView> outputUnorderedView;
	CelComputeShader &shader;
	uint width, height;
public:
	CelPass(CelComputeShader &shader, uint width, uint height);
	~CelPass();

	void Init(ComPtr<ID3D11Device> device);
	ComPtr<ID3D11ShaderResourceView> Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> texture);
};

