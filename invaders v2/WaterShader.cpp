#include "includes.h"
#include "WaterShader.h"
#include "Utils.h"

void WaterShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC cameraDesc, waterDesc, reflectionDesc;

	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.ByteWidth = sizeof(D3DXVECTOR4);
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

	reflectionDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	reflectionDesc.ByteWidth = sizeof(ReflectionType);
	reflectionDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	reflectionDesc.MiscFlags = 0;
	reflectionDesc.StructureByteStride = 0;
	reflectionDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&reflectionDesc, NULL, &reflectionBuffer));
}

void WaterShader::SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, const ComVector<ID3D11ShaderResourceView> &textures)
{
	AssertBool(false, L"not reimplemented");
	ComPtr<ID3D11DeviceContext> con = params.context;

	D3DXMATRIX transform = posMatrix * params.view * params.projection;
	D3DXMatrixTranspose(&transform, &transform);
	Utils::CopyToBuffer(matrixBuffer, transform, con);

	ReflectionType reflection;

	reflection.refraction = params.view * params.projection * posMatrix;
	D3DXMatrixTranspose(&reflection.refraction, &reflection.refraction);
	D3DXMatrixTranspose(&reflection.reflection, &params.reflecMatrix);
	Utils::CopyToBuffer(reflectionBuffer, reflection, con);

	WaterType water;
	water.scale = params.waterScale;
	water.waterTranslation = params.waterTranslation;
	Utils::CopyToBuffer(waterBuffer, water, con);

	con->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	con->VSSetConstantBuffers(1, 1, cameraBuffer.GetAddressOf());
	con->VSSetConstantBuffers(2, 1, reflectionBuffer.GetAddressOf());
	con->PSSetConstantBuffers(0, 1, waterBuffer.GetAddressOf());

	con->IASetInputLayout(layout.Get());

	auto textureCount = textures.size();
	for(unsigned int i = 0; i < textureCount; i++)
		con->PSSetShaderResources(i, 1, textures[i].GetAddressOf());

	con->VSSetShader(vertexShader.Get(), NULL, 0);
	con->PSSetShader(pixelShader.Get(), NULL, 0);

	con->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

void WaterShader::RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount)
{
	TextureShader::RenderShader(context, indexCount);
	for(int i = 1; i < 3; i++)
		context->PSSetShaderResources(i, 1, nullResource.GetAddressOf());
}