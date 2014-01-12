#include "includes.h"
#include "BloomPass.h"
#include "ResourceManager.h"

BloomPass::BloomPass(ComPtr<ID3D11Device> device, uint width, uint height)
:width(width), height(height), halfHeight(height / 2), halfWidth(width / 2),
halfTexture1(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
halfTexture2(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
halfTexture3(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
filterDownPass(RM::Get().GetShader<FilterDownSampleShader>(), halfWidth, halfHeight),
upPass(RM::Get().GetShader<UpSampleComputeShader>(), width, height),
vBlurPass(RM::Get().GetShader<VerticalBlurComputeShader>(), halfWidth , halfHeight),
hBlurPass(RM::Get().GetShader<HorizontalBlurComputeShader>(), halfWidth, halfHeight),
secondBlur(device, halfWidth, halfHeight),
sumPass(RM::Get().GetShader<TexelSumComputeShader>(), width, height),
texture1(device, width, height, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
texture2(device, width, height, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS)
{
}

void BloomPass::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output)
{
	filterDownPass.Pass(context, input, halfTexture1.GetUAV());
	secondBlur.Pass(context, halfTexture1.GetSRV(), halfTexture3.GetUAV());
	vBlurPass.Pass(context, halfTexture1.GetSRV(), halfTexture2.GetUAV());
	hBlurPass.Pass(context, halfTexture2.GetSRV(), halfTexture1.GetUAV());
	upPass.Pass(context, halfTexture1.GetSRV(), texture1.GetUAV());
	upPass.Pass(context, halfTexture3.GetSRV(), texture2.GetUAV());
	sumPass.Pass(context, input, texture1.GetSRV(), texture1.GetUAV());
	sumPass.Pass(context, texture1.GetSRV(), texture2.GetSRV(), output);
}