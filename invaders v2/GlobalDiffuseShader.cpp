#include "GlobalDiffuseShader.h"
#include "Utils.h"

GlobalDiffuseShader::GlobalDiffuseShader(void)
{
}


GlobalDiffuseShader::~GlobalDiffuseShader(void)
{
}

bool GlobalDiffuseShader::Init(ComPtr<ID3D11Device> device)
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

	if(!InitializeShader(device, "GlobalDiffuseVertex.cso", "GlobalDiffusePixel.cso", polygonLayout, numElements))
		return false;

	delete [] polygonLayout;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}

bool GlobalDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightingBufferDesc;

	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));

	lightingBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightingBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightingBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightingBufferDesc.MiscFlags = 0;
	lightingBufferDesc.StructureByteStride = 0;
	lightingBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&lightingBufferDesc, NULL, &lightingBuffer));

	return true;
}

void GlobalDiffuseShader::SetShaderParameters(RenderParams params, D3DXMATRIX moveMatrix)
{
	D3D11_MAPPED_SUBRESOURCE matrixRes, lightingRes;
	ComPtr<ID3D11DeviceContext> cont = params.context;

	D3DXMatrixTranspose(&params.transMatrix, &params.transMatrix);
	cont->Map(matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &matrixRes);
	memcpy(matrixRes.pData, &params.transMatrix, sizeof(D3DXMATRIX));
	cont->Unmap(matrixBuffer.Get(), 0);

	LightBufferType data;
	data.brightness = params.brightness;
	data.diffuseColor = params.diffuseColor;
	data.lightDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f) - params.lightPos;
	D3DXVec3Normalize(&data.lightDir, &data.lightDir);
	cont->Map(lightingBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &lightingRes);
	memcpy(lightingRes.pData, &data, sizeof(LightBufferType));
	cont->Unmap(lightingBuffer.Get(), 0);

	cont->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	cont->PSSetConstantBuffers(0, 1, lightingBuffer.GetAddressOf());

	cont->IASetInputLayout(layout.Get());

	cont->PSSetShader(pixelShader.Get(), NULL, 0);
	cont->VSSetShader(vertexShader.Get(), NULL, 0);
}

void GlobalDiffuseShader::RenderShader(ComPtr<ID3D11DeviceContext> deviceContext, int indexCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexed(indexCount, 0, 0);
 }