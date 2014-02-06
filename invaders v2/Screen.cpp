#include "includes.h"
#include "Screen.h"

Screen::Screen(e::XMFLOAT3 pos)
:pos(pos)
{
	pos.z += 20.0f;
	camera.Move(pos);
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
			child = nullptr;
		return RESULT_CONTINUE;
	}
	else
	{
		return LoopInternal(input, frame);
	}
}