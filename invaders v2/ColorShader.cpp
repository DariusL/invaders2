#include "includes.h"
#include "ColorShader.h"

vector<D3D11_INPUT_ELEMENT_DESC> ColorShader::GetInputLayout()
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

	return ret;
}

void ColorShader::InitializeShaderBuffers(ID3D11Device *device)
{
	IPositionShader::InitializeShaderBuffers(device);
	auto tmp = e::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	colorBuffer = Buffer<e::XMFLOAT4>(device, &tmp);
}


void ColorShader::SetShaderParameters(const RenderParams &params, const XMMATRIX &world)
{
	IPositionShader::SetShaderParameters(params, world);
	params.context->PSSetConstantBuffers(0, 1, colorBuffer.GetAddressOf());
}

void ColorShader::SetShaderParameters(const RenderParams &params, const XMMATRIX &world, const e::XMFLOAT4 color)
{
	colorBuffer.SetData(params.context, color);
	SetShaderParameters(params, world);
}