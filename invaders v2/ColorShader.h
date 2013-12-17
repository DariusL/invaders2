#pragma once

#include "includes.h"

#include "Utils.h"
#include "IPosShader.h"

using namespace std;

class ColorShader : public IPositionShader
{
public:
	ColorShader(wstring vs, wstring ps):IPositionShader(vs, ps){}
	virtual ~ColorShader(void){}

protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();
};