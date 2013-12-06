#pragma once

#include "includes.h"
#include "IInstanceShader.h"

class InstancedTextureShader : public IInstanceShader
{ 
public:
	InstancedTextureShader(wstring vs, wstring ps) :IInstanceShader(vs, ps){}

	virtual void Init(ComPtr<ID3D11Device> device);
	virtual void SetShaderParametersInstancedTextured(const RenderParams &params, const ComVector<ID3D11ShaderResourceView> &textures);
	void SetShaderParametersInstanced(const RenderParams &params){ AssertBool(false, L"SetShaderParametersTextured called on an instance texture shader"); }

	virtual void RenderShaderInstanced(ComPtr<ID3D11DeviceContext> context, int indexCount, int instanceCount);
protected:
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);
	virtual vector<D3D11_INPUT_ELEMENT_DESC> GetInputLayout();

	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11ShaderResourceView> nullResource;
	unsigned int texturesSet;
};