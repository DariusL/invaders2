#pragma once
#include "includes.h"
#include "IDrawable.h"
class Screen : public IDrawable
{
protected:
	e::unique_ptr<Screen> child;
	Camera camera;
	e::XMFLOAT3 pos;
public:
	Screen(e::XMVECTOR pos);
	void Render(const RenderParams &params);
	int Loop(int input, float frame);
	Camera &GetCamera(){ return camera; }
protected:
	virtual void RenderInternal(const RenderParams &params) = 0;
	virtual int LoopInternal(int input, float frame) = 0;
	virtual void DelayInternal() = 0;
};