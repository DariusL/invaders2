#include "PointDiffuseShader.h"
#include "Utils.h"


PointDiffuseShader::PointDiffuseShader(void)
{
}


PointDiffuseShader::~PointDiffuseShader(void)
{
}

bool PointDiffuseShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "PointDiffuseVertex.cso", "PointDiffusePixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}

vector<D3D11_INPUT_ELEMENT_DESC> PointDiffuseShader::GetInputLayout()
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

bool PointDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC pixelLightDesc, vertexLightDesc;

	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.ByteWidth = sizeof(MatrixType);
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));

	pixelLightDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelLightDesc.ByteWidth = sizeof(PixelLightBufferType);
	pixelLightDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelLightDesc.MiscFlags = 0;
	pixelLightDesc.StructureByteStride = 0;
	pixelLightDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&pixelLightDesc, NULL, &pixelLightBuffer));

	vertexLightDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vertexLightDesc.ByteWidth = sizeof(VertexLightBufferType);
	vertexLightDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexLightDesc.MiscFlags = 0;
	vertexLightDesc.StructureByteStride = 0;
	vertexLightDesc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&vertexLightDesc, NULL, &vertexLightBuffer));

	return true;
}

void PointDiffuseShader::SetShaderParameters(RenderParams params, D3DXMATRIX moveMatrix)
{
	D3D11_MAPPED_SUBRESOURCE matrixRes, lightingRes, vertexLightRes;
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

	PixelLightBufferType data;
	data.ambient = D3DXVECTOR4(params.brightness, params.brightness, params.brightness, 1.0f);
	data.diffuseColor = params.diffuseColor;
	cont->Map(pixelLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &lightingRes);
	memcpy(lightingRes.pData, &data, sizeof(PixelLightBufferType));
	cont->Unmap(pixelLightBuffer.Get(), 0);

	D3DXVECTOR4 lightPos = params.lightPos;
	lightPos.w = 1.0f;
	cont->Map(vertexLightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &vertexLightRes);
	memcpy(vertexLightRes.pData, &lightPos, sizeof(VertexLightBufferType));
	cont->Unmap(vertexLightBuffer.Get(), 0);

	cont->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	cont->VSSetConstantBuffers(1, 1, vertexLightBuffer.GetAddressOf());
	cont->PSSetConstantBuffers(0, 1, pixelLightBuffer.GetAddressOf());

	cont->IASetInputLayout(layout.Get());

	cont->PSSetShader(pixelShader.Get(), NULL, 0);
	cont->VSSetShader(vertexShader.Get(), NULL, 0);
}

void PointDiffuseShader::RenderShader(ComPtr<ID3D11DeviceContext> deviceContext, int indexCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexed(indexCount, 0, 0);
 }