#pragma once

#pragma warning(disable : 4005)

#include "includes.h"

#include "Utils.h"
#include "IInstanceShader.h"

using namespace std;

class ColorInstancedShader : public IInstanceShader
{
public:
	ColorInstancedShader(wstring vs, wstring ps) :IInstanceShader(vs, ps){}
	~ColorInstancedShader(void){}

protected:
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

private:
	ComPtr<ID3D11Buffer> matrixBuffer;
};