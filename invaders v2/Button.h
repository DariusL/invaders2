#pragma once
#include "includes.h"
#include "MenuItem.h"
#include "ColorDrawableEntity.h"
#include "PressRegister.h"

class Button : public MenuItem, public ColorDrawableEntity
{
public:
	typedef e::function<void()> PressFunction;
	Button(e::XMVECTOR pos, e::string text, PressFunction &&callback);
	bool Loop();
	void Render(const RenderParams &params){ ColorDrawableEntity::Render(params); }
	void Delay(){ clickRegister.Reset(); }
	void Select(bool selected){ SetScale(selected ? 1.2f : 1.0f); }
private:
	PressFunction callback;
	PressRegister clickRegister;
};