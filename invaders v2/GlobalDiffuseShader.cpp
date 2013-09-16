#include "includes.h"
#include "GlobalDiffuseShader.h"

GlobalDiffuseShader::GlobalDiffuseShader(void)
{
}


GlobalDiffuseShader::~GlobalDiffuseShader(void)
{
}

bool GlobalDiffuseShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "GlobalDiffuseVertex.cso", "GlobalDiffusePixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}

vector<D3D11_INPUT_ELEMENT_DESC> GlobalDiffuseShader::GetInputLayout()
{
		D3D11_INPUT_ELEMENT_DESC desc;
	vector<D3D11_INPUT_ELEMENT_DESC> ret;

	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	ret.push_back(desc);

	desc.SemanticName = "NORMAL";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	ret.push_back(desc);

	desc.SemanticName = "COLOR";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc.InstanceDataStepRate = 0;

	ret.push_back(desc);

	return ret;
}

bool GlobalDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightingBufferDesc;

	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.ByteWidth = sizeof(MatrixType);
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
	MatrixType vertexMatrices;

	params.transMatrix = moveMatrix * params.transMatrix;
	D3DXMatrixTranspose(&params.transMatrix, &params.transMatrix);
	D3DXMatrixTranspose(&moveMatrix, &moveMatrix);
	vertexMatrices.move = moveMatrix;
	vertexMatrices.transform = params.transMatrix;
	cont->Map(matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &matrixRes);
	memcpy(matrixRes.pData, &vertexMatrices, sizeof(MatrixType));
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