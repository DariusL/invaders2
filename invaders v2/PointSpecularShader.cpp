#include "includes.h"
#include "PointSpecularShader.h"
#include "Utils.h"
	
void PointSpecularShader::SetShaderParameters(RenderParams &params, const XMMATRIX &world)
{
	PointDiffuseShader::SetShaderParameters(params, world);

	Utils::CopyToBuffer(cameraBuffer, params.camera->GetPosition(), params.context);

	params.context->VSSetConstantBuffers(3, 1, cameraBuffer.GetAddressOf());
}

void PointSpecularShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	PointDiffuseShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC cameraDesc;

	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.ByteWidth = sizeof(XMFLOAT4);
	cameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraDesc.MiscFlags = 0;
	cameraDesc.StructureByteStride = 0;
	cameraDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&cameraDesc, NULL, &cameraBuffer));
}