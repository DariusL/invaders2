#pragma once
#include "IPosShader.h"

class ITextureShader : public IPositionShader
{
public:
	ITextureShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	virtual ~ITextureShader(){}

	virtual void Init(ComPtr<ID3D11Device> device){IPositionShader::Init(device); InitializeSampler(device);}
	virtual void SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, const ComVector<ID3D11ShaderResourceView> &textures)
	{ 
		IPositionShader::SetShaderParameters(params, posMatrix);
	}

	void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix){ AssertBool(false, L"SetShaderParameters called on a texture shader"); }
protected:
	virtual void InitializeSampler(ComPtr<ID3D11Device> device) = 0;
};