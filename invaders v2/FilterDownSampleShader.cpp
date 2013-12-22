#include "includes.h"
#include "FilterDownSampleShader.h"
#include "Utils.h"

void FilterDownSampleShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC desc;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(FilterBuffer);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&desc, nullptr, &filterBuffer));
}

void FilterDownSampleShader::SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output)
{
	ComputeShader::SetShaderParameters(context, input, output);

	float threshold = 0.6f;

	Utils::CopyToBuffer(filterBuffer, threshold, context);

	context->CSSetConstantBuffers(0, 1, filterBuffer.GetAddressOf());
}