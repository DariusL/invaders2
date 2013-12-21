#pragma once
#include "IPass.h"
#include "SimplePass.h"
#include "Texture.h"
class BlurPass : IPass
{
	/*DownSamplePass downPass;
	UpSamplePass upPass;
	HorizontalBlurPass hBlurPass;
	VerticalBlurPass vBlurPass;*/

	uint width, height, halfWidht, halfHeight;

public:
	BlurPass(uint width, uint height);
	virtual ~BlurPass(){}

	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
};

