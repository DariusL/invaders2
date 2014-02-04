#include "includes.h"
#include "GlobalSpecularShader.h"
	
void GlobalSpecularShader::SetShaderParameters(RenderParams &params, const XMMATRIX &world)
{
	GlobalDiffuseShader::SetShaderParameters(params, world);

	Utils::CopyToBuffer(cameraBuffer.Get(), &params.camera->GetPosition(), params.context);

	params.context->VSSetConstantBuffers(2, 1, cameraBuffer.GetAddressOf());
}

void GlobalSpecularShader::InitializeShaderBuffers(ID3D11Device *device)
{
	GlobalDiffuseShader::InitializeShaderBuffers(device);

	cameraBuffer = Buffer<XMFLOAT4>(device);
}