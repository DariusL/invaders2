#pragma once

#include "includes.h"
#include "IInstanceShader.h"

class InstancedTextureShader : public IInstanceShader
{ 
public:
	InstancedTextureShader(e::wstring vs, e::wstring ps) :IInstanceShader(vs, ps){}
	virtual ~InstancedTextureShader(){}
	virtual void Init(ID3D11Device *device);
	virtual void SetShaderParametersInstancedTextured(const RenderParams &params, const e::vector<ID3D11ShaderResourceView*> &textures);
	void SetShaderParametersInstanced(const RenderParams &params){ using namespace e; AssertBool(false, L"SetShaderParametersTextured called on an instance texture shader"); }

	virtual void RenderShaderInstanced(ID3D11DeviceContext *context, int indexCount, int instanceCount);
protected:
	virtual void InitializeSampler(ID3D11Device *device);
	virtual e::vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	e::ComPtr<ID3D11SamplerState> samplerState;
	unsigned int texturesSet;
};

