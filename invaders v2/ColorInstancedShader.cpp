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

	desc.SemanticName = "POSITION";
	desc.SemanticIndex = 1;
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc.InputSlot = 1;
	desc.AlignedByteOffset = 0;
	desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	desc.InstanceDataStepRate = 1;

	ret.push_back(desc);

	desc.SemanticName = "COLOR";
	desc.SemanticIndex = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.InputSlot = 1;
	desc.AlignedByteOffset = 16;
	desc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	desc.InstanceDataStepRate = 1;

	ret.push_back(desc);

	return ret;
}

void ColorInstancedShader::SetShaderParametersInstanced(RenderParams &params)
{
	IInstanceShader::SetShaderParametersInstanced(params);
}