#pragma once
#include "includes.h"
#include "MenuItem.h"
#include "DrawableEntity.h"
#include "InputRegister.h"

class Button : public MenuItem, public SimpleDrawableEntity
{
public:
	typedef e::function<void()> PressFunction;
	Button(e::XMFLOAT3 pos, e::string text, PressFunction &&callback);
	bool Loop(int input);
private:
	PressFunction callback;
	InputRegister clickRegister;
};