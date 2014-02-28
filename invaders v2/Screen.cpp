#include "includes.h"
#include "Screen.h"

Screen::Screen(e::XMVECTOR pos)
:childResult(RESULT_CONTINUE)
{
	e::XMStoreFloat3(&this->pos, pos);
	camera.Move(e::XMVectorAdd(pos, e::XMVectorSet(0.0f, 0.0f, 50.0f, 0.0f)));
}

void Screen::Render(const RenderParams &params)
{
	if (child != nullptr)
	{
		child->Render(params);
	}
	else
	{
		RenderInternal(params);
	}
}

int Screen::Loop(int input, int frame)
{
	if (child != nullptr)
	{
		childResult = child->Loop(input, frame);
		if (childResult != RESULT_CONTINUE)
		{
			child = nullptr;
			DelayInternal();
		}
		return RESULT_CONTINUE;
	}
	else
	{
		return LoopInternal(input, frame);
	}
}