#pragma once
#include "includes.h"
#include "Globals.h"
#include "Buffer.h"
class ComputeShader
{
private:
	e::wstring cs;
	Buffer<e::XMUINT4> dimmBuffer;
protected:
	e::ComPtr<ID3D11ComputeShader> shader;
public:
	ComputeShader(e::wstring cs):cs(cs){}
	ComputeShader(ComputeShader&) = delete;
	ComputeShader &operator=(ComputeShader&) = delete;
	virtual ~ComputeShader(){}

	void Init(ID3D11Device *device);
	virtual void Start(ID3D11DeviceContext *context, uint width, uint height);
	virtual void SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
protected:
	void InitializeShader(ID3D11Device *device, e::wstring cs);
	virtual void InitializeShaderBuffers(ID3D11Device *device){}
public:
	static const uint groupX;
	static const uint groupY;
};

