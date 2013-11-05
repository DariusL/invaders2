#pragma once
#include "PointSpecularShader.h"
#include "Utils.h"
#include "ITextureShader.h"

class NormalMappedShader : public PointSpecularShader
{
public:
	NormalMappedShader(string vs, string ps):PointSpecularShader(vs, ps){}
	~NormalMappedShader(void){}

	virtual void SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, ComPtr<ID3D11ShaderResourceView> texture);
	virtual void Init(ComPtr<ID3D11Device> device){PointSpecularShader::Init(device); InitializeSampler(device);}
protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	virtual bool InitializeSampler(ComPtr<ID3D11Device> device);
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	
	ComPtr<ID3D11SamplerState> samplerState;
};

