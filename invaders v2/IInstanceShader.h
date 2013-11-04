#pragma once 

#include "IPosShader.h"

class IInstanceShader : public IPositionShader
{
public:
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount) = 0;
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount) = 0;

	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix) = 0;
	virtual void SetShaderParameters(const RenderParams &params) = 0;
};