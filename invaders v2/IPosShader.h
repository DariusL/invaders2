#pragma once

#include "IShader.h"

class IPositionShader : public IShader
{
public:
	IPositionShader(wstring vs, wstring ps):IShader(vs, ps){}
	virtual ~IPositionShader(){}

	virtual void SetShaderParameters(const RenderParams &params, D3DXMATRIX posMatrix) = 0;
};