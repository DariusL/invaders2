#include "ColorInstancedShader.h"


ColorInstancedShader::ColorInstancedShader(void)
{
}


ColorInstancedShader::~ColorInstancedShader(void)
{
}

bool ColorInstancedShader::Init(ComPtr<ID3D11Device> device)
{
	if(!InitializeShader(device, "ColorInstancedVertex.cso", "ColorPixel.cso", GetInputLayout()))
		return false;

	if(!InitializeShaderBuffers(device))
		return false;

	return true;
}

vector<D3D11_INPUT_ELEMENT_DESC> ColorInstancedShader::GetInputLayout()
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

bool ColorInstancedShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightingBufferDesc;
	

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	Assert(device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer));

	lightingBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightingBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
	lightingBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightingBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightingBufferDesc.MiscFlags = 0;
	lightingBufferDesc.StructureByteStride = 0;

	Assert(device->CreateBuffer(&lightingBufferDesc, NULL, &lightingBuffer));

	return true;
}

void ColorInstancedShader::SetShaderParameters(RenderParams params)
{
	D3D11_MAPPED_SUBRESOURCE matrixRes, lightingRes;
	D3DXVECTOR4 brightnessVector = D3DXVECTOR4(params.brightness, params.brightness, params.brightness, 1.0f);

	D3DXMatrixTranspose(&params.transMatrix, &params.transMatrix);

	params.context->Map(matrixBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &matrixRes);
	memcpy(matrixRes.pData, &params.transMatrix, sizeof(D3DXMATRIX));
	params.context->Unmap(matrixBuffer.Get(), 0);

	params.context->Map(lightingBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &lightingRes);
	memcpy(lightingRes.pData, &brightnessVector, sizeof(D3DXVECTOR4));
	params.context->Unmap(lightingBuffer.Get(), 0);

	params.context->VSSetConstantBuffers(0, 1, matrixBuffer.GetAddressOf());
	params.context->PSSetConstantBuffers(0, 1, lightingBuffer.GetAddressOf());

	params.context->IASetInputLayout(layout.Get());

	params.context->VSSetShader(vertexShader.Get(), NULL, 0);
	params.context->PSSetShader(pixelShader.Get(), NULL, 0);
}

void ColorInstancedShader::RenderShader(ComPtr<ID3D11DeviceContext> deviceContext, int indexCount, int instanceCount)
{
	//unleash the grafiks
	deviceContext->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
}