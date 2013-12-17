#pragma once
#include "PointSpecularShader.h"
#include "Utils.h"

class NormalMappedShader : public PointSpecularShader
{
public:
	NormalMappedShader(wstring vs, wstring ps):PointSpecularShader(vs, ps){}
	virtual ~NormalMappedShader(void){}

	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, ComPtr<ID3D11ShaderResourceView> texture);
	virtual void Init(ComPtr<ID3D11Device> device){PointSpecularShader::Init(device); InitializeSampler(device);}
protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);
	
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
};

