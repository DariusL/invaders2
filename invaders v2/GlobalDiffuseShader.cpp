#include "GlobalDiffuseShader.h"


GlobalDiffuseShader::GlobalDiffuseShader(void)
{
}


GlobalDiffuseShader::~GlobalDiffuseShader(void)
{
}

bool GlobalDiffuseShader::Init(ComPtr<ID3D11Device> device)
{
	return false;
}

bool GlobalDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	return false;
}

void GlobalDiffuseShader::SetShaderParameters(RenderParams params, D3DXMATRIX moveMatrix)
{
	
}

void GlobalDiffuseShader::RenderShader(ComPtr<ID3D11DeviceContext> deviceContext, int indexCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexed(indexCount, 0, 0);
 }