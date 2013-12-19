#include "includes.h"
#include "CelPass.h"
#include "Utils.h"

CelPass::CelPass(CelComputeShader &shader, uint width, uint height)
:shader(shader), width(width), height(height)
{
}


CelPass::~CelPass()
{
}

void CelPass::Init(ComPtr<ID3D11Device> device)
{
}

void CelPass::Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output)
{
	shader.SetShaderParameters(context, input, output);
	shader.Start(context, width, height);
}