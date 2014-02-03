#pragma once

#include "Globals.h"
#include "Utils.h"

using namespace Microsoft::WRL;
using namespace std;

class IShader
{
public:
	IShader(wstring vs, wstring ps){ this->vs = vs; this->ps = ps; }
	IShader(IShader&) = delete;
	IShader &operator=(IShader&) = delete;
	virtual ~IShader(){}
	virtual void Init(ID3D11Device *device);
	virtual void RenderShader(ID3D11DeviceContext *context, int indexCount){context->DrawIndexed(indexCount, 0, 0);}
	virtual void SetShader(RenderParams &params);
protected:
	void InitializeShader(ID3D11Device *device, wstring vs, wstring ps, const vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout);
	virtual void InitializeShaderBuffers(ID3D11Device *device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() = 0;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11Buffer> matrixBuffer;
private:
	wstring vs, ps;
};