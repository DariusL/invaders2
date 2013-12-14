#pragma once
#include "includes.h"
#include "RenderTarget.h"

template<class L>
class RenderBall
{
protected:
	RenderTarget firstTarget;
	RenderTarget secondTarget;
	bool useFirst;
	L lambda;
public:
	RenderBall(int width, int height, L &&lambda);
	RenderBall(RenderBall&) = delete;
	RenderBall(RenderBall&&);

	ComPtr<ID3D11ShaderResourceView> GetCurrentTexture(){ return useFirst ? secondTarget.GetRenderedTexture() : firstTarget.GetRenderedTexture(); }
	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params);
	void Init(ComPtr<ID3D11Device> device);
	void Swap(){ useFirst = !useFirst; }
};

template<class L>
RenderBall<L>::RenderBall(int width, int height, L &&lambda)
:firstTarget(width, height), secondTarget(width, height), useFirst(true), lambda(lambda)
{
}

template<class L>
void RenderBall<L>::Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params)
{
	auto &target = useFirst ? firstTarget : secondTarget;
	target.SetRenderTarget(context);
	target.ClearTarget(context);
}

template<class L>
void RenderBall<L>::Init(ComPtr<ID3D11Device> device)
{
	firstTarget.Init(device);
	secondTarget.Init(device);
}

template<class L>
RenderBall<L>::RenderBall(RenderBall &&other)
:useFirst(other.useFirst), firstTarget(std::move(other.firstTarget)), secondTarget(std::move(other.secondTarget)), lambda(move(other.lambda))
{
}