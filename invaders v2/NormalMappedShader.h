#pragma once
#include "PointSpecularShader.h"
#include "Utils.h"

class NormalMappedShader : public PointSpecularShader
{
public:
	NormalMappedShader(void);
	~NormalMappedShader(void);

	virtual bool Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix);
protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
	
	ComPtr<ID3D11SamplerState> samplerState;
};

