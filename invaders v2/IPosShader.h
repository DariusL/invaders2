#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
public:
	virtual void SetShaderParameters(RenderParams params, D3DXMATRIX posMatrix) = 0;
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount) = 0;

};