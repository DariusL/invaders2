#pragma once

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(wstring vs, wstring ps) :IInstanceShader(vs, ps){}
	virtual ~ColorInstancedShader(void){}

protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
};