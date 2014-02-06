#pragma once
#include "includes.h"
#include "MenuItem.h"
#include "DrawableEntity.h"
#include "InputRegister.h"

class Button : public MenuItem, public SimpleDrawableEntity
{
public:
	typedef e::function<void()> PressFunction;
	Button(e::XMVECTOR pos, e::string text, PressFunction &&callback);
	bool Loop(int input);
	void Render(const RenderParams &params){ SimpleDrawableEntity::Render(params); }
private:
	PressFunction callback;
	InputRegister clickRegister;
};