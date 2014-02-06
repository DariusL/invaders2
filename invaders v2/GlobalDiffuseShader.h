#pragma once
#include "iposshader.h"
#include "Utils.h"

class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	virtual ~GlobalDiffuseShader(void){}

public:	
	virtual void SetShaderParameters(const RenderParams &params, const XMMATRIX &world);

protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDir;
		float brightness;
	};

	Buffer<LightBufferType> lightingBuffer;
};

