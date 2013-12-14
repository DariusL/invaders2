#include "includes.h"
#include "CelShader.h"
#include "App.h"

void CelShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	CelBuffer data;
	data.offset = 0.2f;
	data.kernelX = XMFLOAT3X3(1, 0, -1, 2, 0, -2, 1, 0, -1);
	data.kernelY = XMFLOAT3X3(1, 2, 1, 0, 0, 0, -1, -2, -1);

	int width, height;
	App::Get()->GetScreenDims(width, height);
	float fwidth = 1.0f / width;
	float fheight = 1.0f / height;
	data.xOffset = XMFLOAT3(-fwidth, 0.0f, fwidth);
	data.yOffset = XMFLOAT3(-fheight, 0.0f, fheight);

	resource.pSysMem = &data;
	resource.SysMemPitch = 0;
	resource.SysMemSlicePitch = 0;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(XMMATRIX);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	Assert(device->CreateBuffer(&desc, &resource, &celBuffer));
}