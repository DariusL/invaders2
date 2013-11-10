#pragma once
#include "MirrorShader.h"
#include "includes.h"
using namespace std;
class WaterShader : public MirrorShader
{
public:
	WaterShader(wstring vs, wstring ps) :MirrorShader(vs, ps){}
	~WaterShader(void){}

public:
	virtual void SetShaderParametersTextured(const RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
	ComPtr<ID3D11Buffer> waterBuffer;
};