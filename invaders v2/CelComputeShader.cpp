#include "includes.h"
#include "CelComputeShader.h"
#include "Utils.h"

using namespace DirectX;

void CelComputeShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	KernelBuffer kernelData;
	OffsetBuffer offsetData;

	//such c++
#if KERNEL == SOBEL
	offsetData.offset = 0.2f;
	kernelData.kernelX = XMFLOAT4X4(1, 0, -1, 0, 2, 0, -2, 0, 1, 0, -1, 0, 0, 0, 0, 0);
#else
	offsetData.offset = -0.2f;
	kernelData.kernelX = XMFLOAT4X4(3, 10, 3, 0, 0, 0, 0, 0, -3, -10, -3, 0, 0, 0, 0, 0);
#endif
	//much RAII	
	XMStoreFloat4x4(&kernelData.kernelY, XMMatrixTranspose(XMLoadFloat4x4(&kernelData.kernelX)));

	resource.pSysMem = &kernelData;
	resource.SysMemPitch = 0;
	resource.SysMemSlicePitch = 0;

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(KernelBuffer);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	Assert(device->CreateBuffer(&desc, &resource, &kernelBuffer));

	desc.ByteWidth = sizeof(OffsetBuffer);
	resource.pSysMem = &offsetData;

	Assert(device->CreateBuffer(&desc, &resource, &offsetBuffer));
}

void CelComputeShader::SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComVector<ID3D11ShaderResourceView> textures)
{
	ComputeShader::SetShaderParameters(context, textures);

	context->CSSetConstantBuffers(0, 1, kernelBuffer.GetAddressOf());
	context->CSSetConstantBuffers(1, 1, offsetBuffer.GetAddressOf());
}