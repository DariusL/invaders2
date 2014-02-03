#pragma once
#include "IPass.h"
#include "SimplePass.h"
#include "Texture.h"
class BlurPass : IPass
{
	uint width, height, halfWidth, halfHeight;

	DownSamplePass downPass;
	UpSamplePass upPass;
	HorizontalBlurPass hBlurPass;
	VerticalBlurPass vBlurPass;

	Texture halfTexture1, halfTexture2;
public:
	BlurPass(ID3D11Device *device, uint width, uint height);
	virtual ~BlurPass(){}

	virtual void Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
};

