#pragma once
#include "includes.h"
#include "Globals.h"
#include "Input.h"

class PressRegister
{
	int key;
	bool pressed;
public:
	PressRegister(int key) :key(key), pressed(true){}
	inline bool IsDown(){ return Input::IsKeyDown(key); }
	inline void Reset(){ pressed = true; }
	inline bool Register()
	{
		bool down = IsDown();
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