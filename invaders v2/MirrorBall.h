#pragma once
#include "includes.h"
#include "RenderBall.h"

class MirrorBall : public RenderBall<MirrorPrepare>
{
public:
	MirrorBall(int width, int height, MirrorPrepare &&lambda)
	:RenderBall(width, height, forward<MirrorPrepare>(lambda))
	{
	}
	MirrorBall(MirrorBall&) = delete;
	MirrorBall(MirrorBall &&other)
	:RenderBall(move(other))
	{
	}


	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params)
	{
		RenderBall::Prepare(context, params);
		lambda(params);
	}
};