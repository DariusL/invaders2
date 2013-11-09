#include "includes.h"
#include "PointDiffuseShader.h"
#include "Utils.h"

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

void PointDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
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
}

void PointDiffuseShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX moveMatrix)
{
	ComPtr<ID3D11DeviceContext> cont = params.context;
	MatrixType vertexMatrices;

	//vertex shader transformacijos matricos
	vertexMatrices.view = params.view;
	vertexMatrices.projection = params.projection;
	vertexMatrices.world = moveMatrix;

	D3DXMatrixTranspose(&vertexMatrices.view, &vertexMatrices.view);
	D3DXMatrixTranspose(&vertexMatrices.projection, &vertexMatrices.projection);
	D3DXMatrixTranspose(&vertexMatrices.world, &vertexMatrices.world);

	Utils::CopyToBuffer(matrixBuffer, vertexMatrices, cont);

	//pixel shader sviesos duomenys
	PixelLightBufferType data;
	data.ambient = D3DXVECTOR4(params.brightness, params.brightness, params.brightness, 1.0f);
	data.diffuseColor = params.diffuseColor;
	Utils::CopyToBuffer(pixelLightBuffer, data, cont);

	//vertex shader sviesos duomenys
	D3DXVECTOR4 lightPos = params.lightPos;
	lightPos.w = 1.0f;
	Utils::CopyToBuffer(vertexLightBuffer, lightPos, cont);

	//nustatomi konstantu buferiai
	cont->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	cont->VSSetConstantBuffers(1, 1, vertexLightBuffer.GetAddressOf());
	cont->PSSetConstantBuffers(0, 1, pixelLightBuffer.GetAddressOf());

	cont->IASetInputLayout(layout.Get());

	cont->PSSetShader(pixelShader.Get(), NULL, 0);
	cont->VSSetShader(vertexShader.Get(), NULL, 0);
}