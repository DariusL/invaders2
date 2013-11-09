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

void ColorShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));
}

void ColorShader::SetShaderParameters(const RenderParams &params, D3DXMATRIX moveMatrix)
{
	AssertBool(false, L"not reimplemented");
	/*D3DXMATRIX transpose(moveMatrix * params.transMatrix);

	D3DXMatrixTranspose(&transpose, &transpose);

	Utils::CopyToBuffer(matrixBuffer, transpose, params.context);*/

	params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());

	params.context->IASetInputLayout(layout.Get());

	params.context->VSSetShader(vertexShader.Get(), NULL, 0);
	params.context->PSSetShader(pixelShader.Get(), NULL, 0);
}