#include "GlobalSpecularShader.h"


GlobalSpecularShader::GlobalSpecularShader(void)
{
}


GlobalSpecularShader::~GlobalSpecularShader(void)
{
}

bool GlobalSpecularShader::Init(ComPtr<ID3D11Device> device)
{
	unsigned int numElements = 3;
	D3D11_INPUT_ELEMENT_DESC *polygonLayout = new D3D11_INPUT_ELEMENT_DESC[numElements];

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "COLOR";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	if(!InitializeShader(device, "GlobalSpecularVertex.cso", "GlobalSpecularPixel.cso", polygonLayout, numElements))
		return false;

	delete [] polygonLayout;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}
	
void GlobalSpecularShader::SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix)
{
	GlobalDiffuseShader::SetShaderParameters(params, posMatrix);

	D3D11_MAPPED_SUBRESOURCE cameraData;

	params.context->Map(cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &cameraData);
	memcpy(cameraData.pData, params.cameraPos, sizeof(D3DXVECTOR3));
	params.context->Unmap(cameraBuffer.Get(), 0);

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