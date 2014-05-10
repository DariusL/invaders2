#pragma once
#include "iposshader.h"
#include "Utils.h"

class GlobalDiffuseShader : public IPositionShader
{
public:
	GlobalDiffuseShader(e::wstring vs, e::wstring ps) :IPositionShader(vs, ps){}
	virtual ~GlobalDiffuseShader(void){}

public:	
	virtual void SetShaderParameters(RenderParams &params, const e::XMMATRIX &world);

protected:
	virtual void InitializeShaderBuffers(ID3D11Device *device);
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	struct LightBufferType
	{
		e::XMFLOAT4 diffuseColor;
		e::XMFLOAT3 lightDir;
		float brightness;
	};

	Buffer<LightBufferType> lightingBuffer;
};

