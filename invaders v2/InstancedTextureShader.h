#pragma once

#include "includes.h"
#include "IInstanceShader.h"

class InstancedTextureShader : public IInstanceShader
{ 
public:
	InstancedTextureShader(wstring vs, wstring ps) :IInstanceShader(vs, ps){}
	virtual ~InstancedTextureShader(){}
	virtual void Init(ID3D11Device *device);
	virtual void SetShaderParametersInstancedTextured(RenderParams &params, const vector<ID3D11ShaderResourceView*> &textures);
	void SetShaderParametersInstanced(RenderParams &params){ AssertBool(false, L"SetShaderParametersTextured called on an instance texture shader"); }

	virtual void RenderShaderInstanced(ID3D11DeviceContext *context, int indexCount, int instanceCount);
protected:
	virtual void InitializeSampler(ID3D11Device *device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11SamplerState> samplerState;
	unsigned int texturesSet;
};

