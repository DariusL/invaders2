#pragma once
#include "ITextureShader.h"
class TextureShader : public ITextureShader
{
public:
	TextureShader(wstring vs, wstring ps):ITextureShader(vs, ps){}
	~TextureShader(void){}

	virtual void SetShaderParametersTextured(const RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
	unsigned int texturesSet;
};

