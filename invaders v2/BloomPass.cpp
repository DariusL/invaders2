#include "includes.h"
#include "BloomPass.h"
#include "ResourceManager.h"

BloomPass::BloomPass(ComPtr<ID3D11Device> device, uint width, uint height)
:width(width), height(height), halfHeight(height / 2), halfWidth(width / 2),
halfTexture1(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
halfTexture2(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
filterDownPass(RM::Get().GetShader<FilterDownSampleShader>(), halfWidth, halfHeight),
upPass(RM::Get().GetShader<UpSampleComputeShader>(), width, height),
vBlurPass(RM::Get().GetShader<VerticalBlurComputeShader>(), halfWidth , halfHeight),
hBlurPass(RM::Get().GetShader<HorizontalBlurComputeShader>(), halfWidth, halfHeight)
{
}

void BloomPass::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output)
{
	filterDownPass.Pass(context, input, halfTexture1.GetUAV());
	vBlurPass.Pass(context, halfTexture1.GetSRV(), halfTexture2.GetUAV());
	hBlurPass.Pass(context, halfTexture2.GetSRV(), halfTexture1.GetUAV());
	upPass.Pass(context, halfTexture1.GetSRV(), output);
}