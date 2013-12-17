#pragma once
#include "IPosShader.h"
class TextureShader : public IPositionShader
{
public:
	TextureShader(wstring vs, wstring ps) :IPositionShader(vs, ps){}
	virtual ~TextureShader(void){}

	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);
	void SetShaderParameters(RenderParams &params, const XMMATRIX &world){ AssertBool(false, L"SetShaderParameters called on a texture shader"); }
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
	unsigned int texturesSet;
};

