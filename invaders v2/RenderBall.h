#pragma once
#include "includes.h"
#include "RenderTarget.h"

class RenderBall
{
protected:
	RenderTarget firstTarget;
	RenderTarget secondTarget;
	bool useFirst;
public:
	RenderBall(int width, int height);
	RenderBall(RenderBall&) = delete;
	RenderBall(RenderBall&&);

	ComPtr<ID3D11ShaderResourceView> GetCurrentTexture(){ return useFirst ? secondTarget.GetRenderedTexture() : firstTarget.GetRenderedTexture(); }
	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params);
	void Init(ComPtr<ID3D11Device> device);
	void Swap(){ useFirst = !useFirst; }
};