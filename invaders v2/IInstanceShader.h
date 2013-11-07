#pragma once 

#include "IPosShader.h"

class IInstanceShader : public IPositionShader
{
public:
	IInstanceShader(wstring vs, wstring ps) :IPositionShader(vs, ps){}
	virtual ~IInstanceShader(){}
	virtual void RenderShaderInstanced(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount) = 0;

	void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix){}

	virtual void SetShaderParametersInstanced(const RenderParams &params) = 0;
};