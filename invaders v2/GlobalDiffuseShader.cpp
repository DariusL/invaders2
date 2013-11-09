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
	IPositionShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC lightingBufferDesc;

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
	IPositionShader::SetShaderParameters(params, moveMatrix);

	ComPtr<ID3D11DeviceContext> cont = params.context;

	LightBufferType data;
	data.brightness = params.brightness;
	data.diffuseColor = params.diffuseColor;
	data.lightDir = ZeroVec3 - params.lightPos;
	D3DXVec3Normalize(&data.lightDir, &data.lightDir);
	Utils::CopyToBuffer(lightingBuffer, data, cont);

	cont->PSSetConstantBuffers(0, 1, lightingBuffer.GetAddressOf());

	cont->IASetInputLayout(layout.Get());

	cont->PSSetShader(pixelShader.Get(), NULL, 0);
	cont->VSSetShader(vertexShader.Get(), NULL, 0);
}