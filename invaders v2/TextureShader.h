#pragma once
#include "IPosShader.h"
class TextureShader : public IPositionShader
{
public:
	TextureShader(e::wstring vs, e::wstring ps) :IPositionShader(vs, ps){}
	virtual ~TextureShader(void){}

	virtual void Init(ID3D11Device *device);
	virtual void SetShaderParametersTextured(RenderParams &params, const e::XMMATRIX &world, const e::vector<ID3D11ShaderResourceView*> &textures);
	void SetShaderParameters(RenderParams &params, const e::XMMATRIX &world){ using namespace e; AssertBool(false, L"SetShaderParameters called on a texture shader"); }
	virtual void RenderShader(ID3D11DeviceContext *context, int indexCount);

protected:
	virtual void InitializeSampler(ID3D11Device *device);
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	e::ComPtr<ID3D11SamplerState> samplerState;
	unsigned int texturesSet;
};

