#pragma once
#include "ITextureShader.h"
class TextureShader : public ITextureShader
{
public:
	TextureShader(void);
	~TextureShader(void);

	virtual bool Init(ComPtr<ID3D11Device>);
	virtual void SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual bool InitializeSampler(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
};

