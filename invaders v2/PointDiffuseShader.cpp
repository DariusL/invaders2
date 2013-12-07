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
	IPositionShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC pixelLightDesc, vertexLightDesc;

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

void PointDiffuseShader::SetShaderParameters(const RenderParams &params, const XMMATRIX &world)
{
	ComPtr<ID3D11DeviceContext> cont = params.context;
	IPositionShader::SetShaderParameters(params, world);

	//pixel shader sviesos duomenys
	PixelLightBufferType data;
	data.ambient = XMFLOAT4(params.brightness, params.brightness, params.brightness, 1.0f);
	data.diffuseColor = params.diffuseColor;
	Utils::CopyToBuffer(pixelLightBuffer, data, cont);

	//vertex shader sviesos duomenys
	Utils::CopyToBuffer(vertexLightBuffer, params.lightPos, cont);

	//nustatomi konstantu buferiai
	cont->VSSetConstantBuffers(2, 1, vertexLightBuffer.GetAddressOf());
	cont->PSSetConstantBuffers(0, 1, pixelLightBuffer.GetAddressOf());

	SetShader(params);
}