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

	void Init(ComPtr<ID3D11Device> device);
	virtual void Start(ComPtr<ID3D11DeviceContext> context, uint width, uint height);
	virtual void SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output);
protected:
	void InitializeShader(ComPtr<ID3D11Device> device, wstring cs);
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device){}
public:
	static const uint groupX;
	static const uint groupY;
};

