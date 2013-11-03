#include "includes.h"
#include "WaterShader.h"
#include "Utils.h"

WaterShader::WaterShader(void)
{
}


WaterShader::~WaterShader(void)
{
}

bool WaterShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "WaterVertex.cso", "WaterPixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	if(!InitializeSampler(device))
		return false;

	return true;
}

bool WaterShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));

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

	return true;
}

void WaterShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix, vector<ComPtr<ID3D11ShaderResourceView>> textures)
{
	ComPtr<ID3D11DeviceContext> con = params.context;

	D3DXMATRIX transform = posMatrix * params.transMatrix;
	D3DXMatrixTranspose(&transform, &transform);
	Utils::CopyToBuffer(matrixBuffer, transform, con);

	ReflectionType reflection;

	reflection.refraction = params.transMatrix * posMatrix;
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
	for(auto i = 0; i < textureCount; i++)
		con->PSSetShaderResources(i, 1, textures[i].GetAddressOf());

	con->VSSetShader(vertexShader.Get(), NULL, 0);
	con->PSSetShader(pixelShader.Get(), NULL, 0);

	con->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

void WaterShader::RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount)
{
	TextureShader::RenderShader(context, indexCount);
	for(int i = 0; i < 3; i++)
		context->PSSetShaderResources(i, 1, nullResource.GetAddressOf());
}