#pragma once
#include "includes.h"
#include "Globals.h"
using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
class ComputeShader
{
private:
	wstring cs;
protected:
	ComPtr<ID3D11ComputeShader> shader;
public:
	ComputeShader(wstring cs):cs(cs){}
	ComputeShader(ComputeShader&) = delete;
	ComputeShader &operator=(ComputeShader&) = delete;
	virtual ~ComputeShader(){}

	void Init(ID3D11Device *device);
	virtual void Start(ID3D11DeviceContext *context, uint width, uint height);
	virtual void SetShaderParameters(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output);
protected:
	void InitializeShader(ID3D11Device *device, wstring cs);
	virtual void InitializeShaderBuffers(ID3D11Device *device){}
public:
	static const uint groupX;
	static const uint groupY;
};

