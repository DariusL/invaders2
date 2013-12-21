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
	RenderBall(ComPtr<ID3D11Device> device, int width, int height, L &&lambda);
	RenderBall(RenderBall&) = delete;
	RenderBall(RenderBall&&);

	ComPtr<ID3D11ShaderResourceView> GetCurrentTexture(){ return useFirst ? secondTarget.GetRenderedTexture() : firstTarget.GetRenderedTexture(); }
	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params);
	void Swap(){ useFirst = !useFirst; }
};

template<class L>
RenderBall<L>::RenderBall(ComPtr<ID3D11Device> device, int width, int height, L &&lambda)
:firstTarget(device, width, height), secondTarget(device, width, height), useFirst(true), lambda(lambda)
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
RenderBall<L>::RenderBall(RenderBall &&other)
:useFirst(other.useFirst), firstTarget(std::move(other.firstTarget)), secondTarget(std::move(other.secondTarget)), lambda(move(other.lambda))
{
}