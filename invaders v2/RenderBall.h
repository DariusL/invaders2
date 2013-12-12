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

	ComPtr<ID3D11ShaderResourceView> GetCurrentTexture(){ return useFirst ? secondTarget.GetRenderedTexture() : firstTarget.GetRenderedTexture(); }
	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params);
	void Init(ComPtr<ID3D11Device> device);
	void Swap(){ useFirst = !useFirst; }
};

RenderBall::RenderBall(int width, int height)
:firstTarget(width, height), secondTarget(width, height), useFirst(true)
{
}

void RenderBall::Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params)
{
	auto &target = useFirst ? firstTarget : secondTarget;
	target.SetRenderTarget(context);
	target.ClearTarget(context);
}

void RenderBall::Init(ComPtr<ID3D11Device> device)
{
	firstTarget.Init(device);
	secondTarget.Init(device);
}