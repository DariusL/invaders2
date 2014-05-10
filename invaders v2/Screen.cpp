#include "includes.h"
#include "Screen.h"
#include "Utils.h"

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
		if (child->ShouldRenderParent())
			RenderInternal(params);
		child->Render(params);
	}
	else
	{
		RenderInternal(params);
	}
}

int Screen::Loop(InputType input, int frame)
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

bool Screen::ShouldRenderParent()
{
	if (child)
		return child->ShouldRenderParent();
	else
		return true;
}

e::XMVECTOR Screen::GetChildPos()
{
	return e::XMVectorAdd(e::XMLoadFloat3(&pos), Utils::VectorSet(0.0f, 0.0f, 20.0f));
}

Camera &Screen::GetCamera()
{
	if (child)
		return child->GetCamera();
	else
		return camera;
}