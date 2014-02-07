#pragma once
#include "includes.h"
#include "Globals.h"
#include "Input.h"
class HoldRegister
{
	int key, time, freq;
public:
	HoldRegister(int key, int freq = 125) :key(key), time(clock()), freq(freq){}
	inline void Reset(){ time = clock(); }
	bool Register()
	{
		int now = clock();
		if (IsDown() && time + freq < now)
		{
			time = now;
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool IsDown()
	{
		return Input::IsKeyDown(key);
	}
};