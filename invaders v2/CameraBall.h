#pragma once
#include "RenderBall.h"
#include "Direct3D.h"

class CameraBall : public RenderBall < std::function < void(RenderParams&, Direct3D&)>>
{
public:
	typedef std::function < void(RenderParams&, Direct3D&)> CameraPrepare;
	CameraBall(int width, int height, CameraPrepare &&lambda)
		:RenderBall(width, height, forward<CameraPrepare>(lambda))
	{
	}
	CameraBall(CameraBall&) = delete;
	CameraBall(CameraBall &&other)
		:RenderBall(move(other))
	{
	}


	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params, Direct3D &direct3D)
	{
		RenderBall::Prepare(context, params);
		lambda(params, direct3D);
	}
};