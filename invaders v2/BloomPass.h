#pragma once
#include "SimplePass.h"
#include "Texture.h"
#include "DoubleInputPass.h"
#include "BlurPass.h"
class BloomPass : public IPass
{
	uint width, height, halfWidth, halfHeight;

	FilterDownSamplePass filterDownPass;
	UpSamplePass upPass;
	HorizontalBlurPass hBlurPass;
	VerticalBlurPass vBlurPass;
	BlurPass secondBlur;


	TexelSumPass sumPass;

	Texture halfTexture1;
	Texture halfTexture2;
	Texture halfTexture3;
	Texture texture1;
	Texture texture2;

public:
	BloomPass(ComPtr<ID3D11Device> device, uint width, uint height);
	virtual ~BloomPass(){}

	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
};

