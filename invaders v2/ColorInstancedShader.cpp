#include "includes.h"
#include "ColorInstancedShader.h"

e::vector<D3D11_INPUT_ELEMENT_DESC> ColorInstancedShader::GetInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC desc;
	e::vector<D3D11_INPUT_ELEMENT_DESC> ret;

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

	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 1;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.InputSlot = 1;
	desc.AlignedByteOffset = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	desc.InstanceDataStepRate = 1;

	ret.push_back(desc);

	return ret;
}

void ColorInstancedShader::SetShaderParametersInstanced(const RenderParams &params, e::XMFLOAT4 color)
{
	colorBuffer.SetData(params.context, color);
	SetShaderParametersInstanced(params);
}

void ColorInstancedShader::SetShaderParametersInstanced(const RenderParams &params)
{
	IInstanceShader::SetShaderParametersInstanced(params);
	params.context->PSSetConstantBuffers(0, 1, colorBuffer.GetAddressOf());
}

void ColorInstancedShader::InitializeShaderBuffers(ID3D11Device *device)
{
	auto tmp = e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	colorBuffer = Buffer<e::XMFLOAT4>(device, &tmp);
	IInstanceShader::InitializeShaderBuffers(device);
}