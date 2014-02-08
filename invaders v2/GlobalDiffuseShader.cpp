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

	desc.SemanticName = "COLOR";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InputSlot = 0;
	desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
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

	return ret;
}

void GlobalDiffuseShader::InitializeShaderBuffers(ID3D11Device *device)
{
	IPositionShader::InitializeShaderBuffers(device);

	lightingBuffer = Buffer<LightBufferType>(device);
}

void GlobalDiffuseShader::SetShaderParameters(const RenderParams &params, const XMMATRIX &world)
{
	IPositionShader::SetShaderParameters(params, world);

	auto cont = params.context;
	XMVECTOR lightdir;

	lightdir = -XMLoadFloat3(&params.lightPos);
	XMVector3Normalize(lightdir);

	LightBufferType data;
	data.brightness = params.brightness;
	data.diffuseColor = params.diffuseColor;
	XMStoreFloat3(&data.lightDir, lightdir);
	lightingBuffer.SetData(cont, data);

	cont->PSSetConstantBuffers(0, 1, lightingBuffer.GetAddressOf());
}