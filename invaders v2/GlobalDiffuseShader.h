#pragma once
#include "iposshader.h"
#include "Utils.h"

class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	~GlobalDiffuseShader(void){}

public:	
	virtual void SetShaderParameters(RenderParams &params, const XMMATRIX &world);

protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11Buffer> lightingBuffer;

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDir;
		float brightness;
	};
};

