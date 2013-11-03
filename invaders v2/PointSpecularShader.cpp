#include "includes.h"
#include "PointSpecularShader.h"
#include "Utils.h"


PointSpecularShader::PointSpecularShader(void)
{
}


PointSpecularShader::~PointSpecularShader(void)
{
}

bool PointSpecularShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "PointSpecularVertex.cso", "PointSpecularPixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}
	
void PointSpecularShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix)
{
	PointDiffuseShader::SetShaderParameters(params, posMatrix);

	Utils::CopyToBuffer(cameraBuffer, params.cameraPos, params.context);

	params.context->VSSetConstantBuffers(2, 1, cameraBuffer.GetAddressOf());
}

bool PointSpecularShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	if(!PointDiffuseShader::InitializeShaderBuffers(device))
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