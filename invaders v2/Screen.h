#pragma once
#include "includes.h"
#include "IDrawable.h"
#include "Input.h"
class Screen : public IDrawable
{
protected:
	e::unique_ptr<Screen> child;
	Camera camera;
	e::XMFLOAT3 pos;
	int childResult;
public:
	Screen(e::XMVECTOR pos);
	void Render(RenderParams &params);
	int Loop(InputType input, int frame);
	Camera &GetCamera();
protected:
	virtual void RenderInternal(RenderParams &params) = 0;
	virtual int LoopInternal(InputType input, int frame) = 0;
	virtual void DelayInternal() = 0;
	virtual bool ShouldRenderParent();
	e::XMVECTOR GetChildPos();
};