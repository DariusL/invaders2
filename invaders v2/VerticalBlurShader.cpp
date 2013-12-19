#include "includes.h"
#include "VerticalBlurShader.h"
#include "App.h"

void VerticalBlurShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	BlurBuffer data;

	int width, height;
	AppHandle::Get().GetScreenDims(width, height);
	float fheight = 1.0f / height;
	data.offset = XMFLOAT4(-fheight, 0.0f, fheight, 0.0f);

	data.weight = XMFLOAT4(1.0f, 0.9f, 0.55f, 0.18f);

	float norm = data.weight.x + 2.0f * (data.weight.y + data.weight.z + data.weight.w);

	data.weight.x /= norm;
	data.weight.y /= norm;
	data.weight.z /= norm;
	data.weight.w /= norm;

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