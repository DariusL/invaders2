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
	void Delay(){ clickRegister.Register(); }
	void Select(bool selected){ SetScale(selected ? 1.2f : 1.0f); }
private:
	PressFunction callback;
	InputRegister clickRegister;
};