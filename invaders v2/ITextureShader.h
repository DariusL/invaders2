#pragma once
#include "IPosShader.h"

class ITextureShader : public IPositionShader
{
public:
	virtual void SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture) = 0;
	void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix){}
protected:
	virtual bool InitializeSampler(ComPtr<ID3D11Device> device) = 0;
};