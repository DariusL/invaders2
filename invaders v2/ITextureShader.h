#pragma once
#include "IShader.h"

class ITextureShader : public IShader
{
public:
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture) = 0;
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount){context->DrawIndexed(indexCount, 0, 0);}
protected:
	virtual bool InitializeSampler(ComPtr<ID3D11Device> device) = 0;
};