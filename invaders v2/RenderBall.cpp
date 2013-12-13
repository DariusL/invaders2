#include "includes.h"
#include "RenderBall.h"

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

RenderBall::RenderBall(RenderBall &&other)
:useFirst(other.useFirst), firstTarget(std::move(other.firstTarget)), secondTarget(std::move(other.secondTarget))
{

}