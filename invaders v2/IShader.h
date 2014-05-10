#pragma once

#include "Globals.h"
#include "Utils.h"
#include "Buffer.h"

class IShader
{
public:
	IShader(e::wstring vs, e::wstring ps){ this->vs = vs; this->ps = ps; }
	IShader(IShader&) = delete;
	IShader &operator=(IShader&) = delete;
	virtual ~IShader(){}
	virtual void Init(ID3D11Device *device);
	virtual void RenderShader(ID3D11DeviceContext *context, int indexCount){context->DrawIndexed(indexCount, 0, 0);}
	virtual void SetShader(RenderParams &params);
protected:
	void InitializeShader(ID3D11Device *device, e::wstring vs, e::wstring ps, const e::vector<D3D11_INPUT_ELEMENT_DESC> &inputLayout);
	virtual void InitializeShaderBuffers(ID3D11Device *device) = 0;
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout() = 0;

	e::ComPtr<ID3D11VertexShader> vertexShader;
	e::ComPtr<ID3D11PixelShader> pixelShader;
	e::ComPtr<ID3D11InputLayout> layout;
private:
	e::wstring vs, ps;
};