#pragma once 

#include "IPosShader.h"

class IInstanceShader : public IPositionShader
{
public:
	IInstanceShader(wstring vs, wstring ps) :IPositionShader(vs, ps){}
	virtual ~IInstanceShader(){}

	virtual void RenderShaderInstanced(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount) = 0;
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount){ AssertBool(false, L"RenderShader called on an instanced shader"); }

	void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix){ AssertBool(false, L"SetShaderParameters called on an instanced shader"); }

	virtual void SetShaderParametersInstanced(const RenderParams &params) = 0;
};