#pragma once
#include "MirrorShader.h"
#include "includes.h"
using namespace std;
class WaterShader : public MirrorShader
{
public:
	WaterShader(wstring vs, wstring ps) :MirrorShader(vs, ps){}
	virtual ~WaterShader(void){}

public:
	virtual void SetShaderParametersTextured(RenderParams &params, const XMMATRIX &world, const ComVector<ID3D11ShaderResourceView> &textures);
protected:
	virtual void InitializeShaderBuffers(ComPtr<ID3D11Device> device);
	virtual void InitializeSampler(ComPtr<ID3D11Device> device);

	ComPtr<ID3D11Buffer> cameraBuffer;
	ComPtr<ID3D11Buffer> waterBuffer;
	ComPtr<ID3D11SamplerState> waterSamplerState;
};