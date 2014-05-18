#pragma once

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(e::wstring vs, e::wstring ps) :IInstanceShader(vs, ps){}
	virtual ~ColorInstancedShader(void){}
protected:
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
};