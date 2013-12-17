#pragma once
#include "TextureShader.h"
class MirrorShader : public TextureShader
{
public:
	MirrorShader(wstring vs, wstring ps) :TextureShader(vs, ps){}
	virtual ~MirrorShader(){}

	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);
protected:
	ComPtr<ID3D11Buffer> reflectionBuffer;

	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
};

