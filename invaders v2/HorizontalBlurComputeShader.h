#pragma once
#include "ComputeShader.h"
class HorizontalBlurComputeShader : public ComputeShader
{
public:
	HorizontalBlurComputeShader(e::wstring cs) : ComputeShader(cs){}
	virtual ~HorizontalBlurComputeShader(){}
	virtual void SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);

	e::ComPtr<ID3D11Buffer> blurBuffer;

	struct BlurBuffer
	{
		DirectX::XMFLOAT4 weight;
		DirectX::XMUINT2 off1;
		DirectX::XMUINT2 off2;
		DirectX::XMUINT2 off3;
		DirectX::XMUINT2 padding;
	};
};

