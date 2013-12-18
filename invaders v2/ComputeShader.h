#pragma once
#include "includes.h"
#include "Globals.h"
using namespace std;
using namespace Microsoft::WRL;

class ComputeShader
{
private:
	wstring cs;
protected:
	ComPtr<ID3D11ComputeShader> shader;
	uint texturesSet;
public:
	ComputeShader(wstring cs):cs(cs), texturesSet(0){}
	ComputeShader(ComputeShader&) = delete;
	ComputeShader &operator=(ComputeShader&) = delete;
	virtual ~ComputeShader(){}

	void Init(ComPtr<ID3D11Device> device);
	virtual void Start(ComPtr<ID3D11DeviceContext> context, uint width, uint height);
	virtual void SetShaderParameters(ComPtr<ID3D11DeviceContext> context, ComVector<ID3D11ShaderResourceView> textures);
protected:
	void InitializeShader(ComPtr<ID3D11Device> device, wstring cs);
	void SetShader(ComPtr<ID3D11DeviceContext> context);
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device){}
public:
	static const uint groupX;
	static const uint groupY;
};

