#pragma once
#include "includes.h"
#include "Globals.h"
#include "Input.h"

class PressRegister
{
	Input::ACTION key;
	bool pressed;
public:
	PressRegister(Input::ACTION key) :key(key), pressed(true){}
	inline bool IsDown(InputType input){ return input[key]; }
	inline void Reset(){ pressed = true; }
	inline bool Register(InputType input)
	{
		bool down = IsDown(input);
		if (down && !pressed)
		{
			return pressed = true;
		}
		if (!down && pressed)
		{
			return pressed = false;
		}
		return false;
	}
};