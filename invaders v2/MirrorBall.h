#pragma once
#include "includes.h"
#include "RenderBall.h"

class MirrorBall : public RenderBall
{
	MirrorPrepare lambda;
public:
	MirrorBall(int width, int height, MirrorPrepare &&lambda)
	:RenderBall(width, height), lambda(std::forward<MirrorPrepare>(lambda))
	{
	}
	MirrorBall(MirrorBall&) = delete;
	MirrorBall(MirrorBall &&other)
	:RenderBall(move(other)), lambda(move(other.lambda))
	{
	}


	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params)
	{
		RenderBall::Prepare(context, params);
		lambda(params);
	}
};