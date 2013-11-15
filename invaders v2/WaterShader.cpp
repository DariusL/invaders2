#include "includes.h"
#include "WaterShader.h"
#include "Utils.h"

void WaterShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	MirrorShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC cameraDesc, waterDesc;

	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.ByteWidth = sizeof(XMFLOAT4);
	cameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraDesc.MiscFlags = 0;
	cameraDesc.StructureByteStride = 0;
	cameraDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&cameraDesc, NULL, &cameraBuffer));

	waterDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	waterDesc.ByteWidth = sizeof(WaterType);
	waterDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	waterDesc.MiscFlags = 0;
	waterDesc.StructureByteStride = 0;
	waterDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&waterDesc, NULL, &waterBuffer));
}

void WaterShader::SetShaderParametersTextured(const RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	MirrorShader::SetShaderParametersTextured(params, world, textures);

	ComPtr<ID3D11DeviceContext> con = params.context;

	WaterType water;
	water.scale = params.waterScale;
	water.waterTranslation = params.waterTranslation;
	Utils::CopyToBuffer(waterBuffer, water, con);

	Utils::CopyToBuffer(cameraBuffer, params.camera->GetPosition(), params.context);

	con->VSSetConstantBuffers(3, 1, cameraBuffer.GetAddressOf());
	con->PSSetConstantBuffers(0, 1, waterBuffer.GetAddressOf());
}