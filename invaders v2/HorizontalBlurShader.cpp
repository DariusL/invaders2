#include "includes.h"
#include "HorizontalBlurShader.h"
#include "App.h"

void HorizontalBlurShader::InitializeShaderBuffers(ComPtr<ID3D11Device> device)
{
	TextureShader::InitializeShaderBuffers(device);

	D3D11_BUFFER_DESC desc;
	D3D11_SUBRESOURCE_DATA resource;
	BlurBuffer data;

	int width, height;
	AppHandle::Get().GetScreenDims(width, height);
	float fwidth = 1.0f / width;
	data.offset = XMFLOAT4(-fwidth, 0.0f, fwidth, 0.0f);

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

void HorizontalBlurShader::SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures)
{
	TextureShader::SetShaderParametersTextured(params, world, textures);

	params.context->PSSetConstantBuffers(0, 1, blurBuffer.GetAddressOf());
}