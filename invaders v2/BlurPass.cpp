#include "includes.h"
#include "BlurPass.h"
#include "ResourceManager.h"

BlurPass::BlurPass(ID3D11Device *device, uint width, uint height)
:width(width), height(height), halfHeight(height / 2), halfWidth(width / 2),
halfTexture1(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
halfTexture2(device, halfWidth, halfHeight, TEXTURE_VIEW_SHADER_RESOURCE | TEXTURE_VIEW_UNORDERED_ACCESS),
downPass(RM::Get().GetShader<DownSampleComputeShader>(), halfWidth, halfHeight),
upPass(RM::Get().GetShader<UpSampleComputeShader>(), width, height),
hBlurPass(RM::Get().GetShader<HorizontalBlurComputeShader>(), halfWidth, halfHeight),
vBlurPass(RM::Get().GetShader<VerticalBlurComputeShader>(), halfWidth, halfHeight)
{
}

void BlurPass::Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output)
{
	downPass.Pass(context, input, halfTexture1.GetUAV());
	vBlurPass.Pass(context, halfTexture1.GetSRV(), halfTexture2.GetUAV());
	hBlurPass.Pass(context, halfTexture2.GetSRV(), halfTexture1.GetUAV());
	upPass.Pass(context, halfTexture1.GetSRV(), output);
}