#include "includes.h"
#include "GlobalDiffuseShader.h"

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

void GlobalDiffuseShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
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
}

void GlobalDiffuseShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX moveMatrix)
{
	ComPtr<ID3D11DeviceContext> cont = params.context;
	MatrixType vertexMatrices;

	AssertBool(false, L"not reimplemented");
	/*vertexMatrices.viewproject = moveMatrix * params.transMatrix;
	vertexMatrices.world = moveMatrix;

	D3DXMatrixTranspose(&vertexMatrices.viewproject, &vertexMatrices.viewproject);
	D3DXMatrixTranspose(&vertexMatrices.world, &vertexMatrices.world);

	Utils::CopyToBuffer(matrixBuffer, vertexMatrices, cont);*/

	LightBufferType data;
	data.brightness = params.brightness;
	data.diffuseColor = params.diffuseColor;
	data.lightDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f) - params.lightPos;
	D3DXVec3Normalize(&data.lightDir, &data.lightDir);
	Utils::CopyToBuffer(lightingBuffer, data, cont);

	cont->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	cont->PSSetConstantBuffers(0, 1, lightingBuffer.GetAddressOf());

	cont->IASetInputLayout(layout.Get());

	cont->PSSetShader(pixelShader.Get(), NULL, 0);
	cont->VSSetShader(vertexShader.Get(), NULL, 0);
}