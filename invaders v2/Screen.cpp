#include "includes.h"
#include "Screen.h"

Screen::Screen(e::XMVECTOR pos)
{
	e::XMStoreFloat3(&this->pos, pos);
	camera.Move(e::XMVectorAdd(pos, e::XMVectorSet(0.0f, 0.0f, 20.0f, 0.0f)));
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

int Screen::Loop(int input, float frame)
{
	if (child != nullptr)
	{
		if (child->Loop(input, frame) == RESULT_CLOSE)
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