#include "includes.h"
#include "GlobalSpecularShader.h"


GlobalSpecularShader::GlobalSpecularShader(void)
{
}


GlobalSpecularShader::~GlobalSpecularShader(void)
{
}

bool GlobalSpecularShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "GlobalSpecularVertex.cso", "GlobalSpecularPixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}
	
void GlobalSpecularShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix)
{
	GlobalDiffuseShader::SetShaderParameters(params, posMatrix);

	Utils::CopyToBuffer(cameraBuffer, &params.cameraPos, params.context);

	params.context->VSSetConstantBuffers(1, 1, cameraBuffer.GetAddressOf());
}

bool GlobalSpecularShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	if(!GlobalDiffuseShader::InitializeShaderBuffers(device))
		return false;

	D3D11_BUFFER_DESC cameraDesc;

	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.ByteWidth = sizeof(D3DXVECTOR4);
	cameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraDesc.MiscFlags = 0;
	cameraDesc.StructureByteStride = 0;
	cameraDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&cameraDesc, NULL, &cameraBuffer));

	return true;
}