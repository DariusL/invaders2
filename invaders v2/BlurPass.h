#pragma once
#include "IPass.h"
#include "SimplePass.h"
#include "Texture.h"
class BlurPass : IPass
{
	DownSamplePass downPass;
	UpSamplePass upPass;
	HorizontalBlurPass hBlurPass;
	VerticalBlurPass vBlurPass;

	Texture halfTexture1, halfTexture2;

	uint width, height, halfWidth, halfHeight;

public:
	BlurPass(ComPtr<ID3D11Device> device, uint width, uint height);
	virtual ~BlurPass(){}

	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
};

