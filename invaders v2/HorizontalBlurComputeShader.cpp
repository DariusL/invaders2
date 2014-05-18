#include "includes.h"
#include "HorizontalBlurComputeShader.h"
#include "Utils.h"

using namespace DirectX;
void HorizontalBlurComputeShader::InitializeShaderBuffers(ID3D11Device *device)
{
	ComputeShader::InitializeShaderBuffers(device);
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	BlurBuffer data;

	//pikseliu svoriai
	data.weight = XMFLOAT4(1.0f, 0.9f, 0.55f, 0.18f);
	float norm = data.weight.x + 2.0f * (data.weight.y + data.weight.z + data.weight.w);

	data.weight.x /= norm;
	data.weight.y /= norm;
	data.weight.z /= norm;
	data.weight.w /= norm;

	//kurie pikseliai naudojami
	data.off1 = XMUINT2(1, 0);
	data.off2 = XMUINT2(2, 0);
	data.off3 = XMUINT2(3, 0);

	resource.pSysMem = &data;
	resource.SysMemPitch = 0;
	resource.SysMemSlicePitch = 0;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(BlurBuffer);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	Assert(device->CreateBuffer(&desc, &resource, &blurBuffer));
}

void HorizontalBlurComputeShader::SetShaderParameters(ID3D11DeviceContext*context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output)
{
	ComputeShader::SetShaderParameters(context, input, output);

	context->CSSetConstantBuffers(1, 1, blurBuffer.GetAddressOf());
}