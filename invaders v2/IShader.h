#pragma once

#include "Globals.h"

using namespace Microsoft::WRL;
using namespace std;

class IShader
{
public:
	IShader(string vs, string ps){this->vs = vs; this->ps = ps;}
	virtual ~IShader(){}
	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void RenderShader(ComPtr<ID3D11DeviceContext> context, int indexCount){context->DrawIndexed(indexCount, 0, 0);}
protected:
	bool InitializeShader(ComPtr<ID3D11Device> device, string vs, string ps, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout);
	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device) = 0;
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() = 0;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;
private:
	IShader(const IShader &other){}
	IShader &operator=(const IShader &other){}
	string vs, ps;
};