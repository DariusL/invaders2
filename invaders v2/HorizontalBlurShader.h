#pragma once
#include "TextureShader.h"
class HorizontalBlurShader : public TextureShader
{
public:
	HorizontalBlurShader(wstring vs, wstring ps) :TextureShader(vs, ps){}
	virtual ~HorizontalBlurShader(){}

	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);

protected:
	ComPtr<ID3D11Buffer> blurBuffer;

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);

	struct BlurBuffer
	{
		DirectX::XMFLOAT4 offset;
		DirectX::XMFLOAT4 weight;
	};
};

