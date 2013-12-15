#pragma once
#include "TextureShader.h"
class CelShader : public TextureShader
{
public:
	CelShader(wstring vs, wstring ps) :TextureShader(vs, ps){}
	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);

protected:
	ComPtr<ID3D11Buffer> kernelBuffer;
	ComPtr<ID3D11Buffer> offsetBuffer;

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);

	struct KernelBuffer
	{
		DirectX::XMFLOAT4X4 kernelX;
		DirectX::XMFLOAT4X4 kernelY;
	};

	struct OffsetBuffer
	{
		DirectX::XMFLOAT3 xOffset;
		float offset;
		DirectX::XMFLOAT3 yOffset;
		float padding;
	};
};

