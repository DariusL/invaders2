#pragma once
#include "includes.h"
#include "RenderBall.h"

template<class Lambda>
class LambdaBall : public RenderBall
{
	Lambda lambda;
	LambdaBall(int width, int height, Lambda &&lambda);
public:
	virtual void Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params);
};

template<class Lambda>
LambdaBall<Lambda>::LambdaBall(int width, int height, Lambda &&lambda)
:RenderBall(width, height), lambda(std::forward<Lambda>(lambda))
{
}

template<class Lambda>
void LambdaBall<Lambda>::Prepare(ComPtr<ID3D11DeviceContext> context, RenderParams &params)
{
	RenderBall::Prepare(context, params);
	lambda(context, params);
}