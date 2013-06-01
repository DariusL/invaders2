#include "Input.h"

Input::Input(void)
{
	for(int i = 0; i < 256; i++)
		keys[i] = false;
}

bool Input::IsKeyDown(int key)
{
	return keys[key];
}

void Input::KeyDown(int key)
{
	keys[key] = true;
}

void Input::KeyUp(int key)
{
	keys[key] = false;
}