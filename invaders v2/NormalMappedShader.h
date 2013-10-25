#pragma once
#include "PointSpecularShader.h"
#include "Utils.h"
#include "ITextureShader.h"

class NormalMappedShader : public PointSpecularShader
{
public:
	NormalMappedShader(void);
	~NormalMappedShader(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture);
protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	virtual bool InitializeSampler(ComPtr<ID3D11Device> device);
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	
	ComPtr<ID3D11SamplerState> samplerState;
};

