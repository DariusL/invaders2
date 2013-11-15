#pragma once
#include "includes.h"
#include "RenderTarget.h"

class RenderBall
{
	RenderTarget firstTarget;
	RenderTarget secondTarget;
	bool useFirst;
public:
	RenderBall(int width, int height);
	~RenderBall();

	ComPtr<ID3D11ShaderResourceView> GetCurrentTexture(){ return useFirst ? secondTarget.GetRenderedTexture() : firstTarget.GetRenderedTexture(); }
	void Prepare(ComPtr<ID3D11DeviceContext> context, const RenderParams &params);
	void Init(ComPtr<ID3D11Device> device);
};