#pragma once
#include "ITextureShader.h"
class TextureShader : public ITextureShader
{
public:
	TextureShader(void);
	~TextureShader(void);

	bool Init(ComPtr<ID3D11Device>);
	void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture);
	void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount);

protected:
	bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	bool InitializeSampler(ComPtr<ID3D11Device> device);
	vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
};

