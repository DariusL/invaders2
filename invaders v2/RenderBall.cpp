#include "includes.h"
#include "RenderBall.h"


RenderBall::RenderBall(int width, int height)
:useFirst(true), firstTarget(width, height), secondTarget(width, height)
{
}


RenderBall::~RenderBall()
{
}

void RenderBall::Prepare(ComPtr<ID3D11DeviceContext> context, const RenderParams &params)
{
	useFirst = !useFirst;
	if (useFirst)
	{
		firstTarget.SetRenderTarget(context);
		firstTarget.ClearTarget(context);
	}
	else
	{
		secondTarget.SetRenderTarget(context);
		secondTarget.ClearTarget(context);
	}
}

void RenderBall::Init(ComPtr<ID3D11Device> device)
{
	firstTarget.Init(device);
	secondTarget.Init(device);
}