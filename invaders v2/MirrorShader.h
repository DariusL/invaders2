#pragma once
#include "TextureShader.h"
class MirrorShader : public TextureShader
{
public:
	MirrorShader(wstring vs, wstring ps) :TextureShader(vs, ps){}
	~MirrorShader(){}

	virtual void SetShaderParametersTextured(const RenderParams &params, D3DXMATRIX posMatrix, const ComVector<ID3D11ShaderResourceView> &textures);
protected:
	ComPtr<ID3D11Buffer> reflectionBuffer;

	virtual bool InitializeShaderBuffers(ComPtr<ID3D11Device> device);
};

