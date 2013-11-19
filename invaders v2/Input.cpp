#include "includes.h"
#include "Input.h"

Input::Input(void)
{
	for(int i = 0; i < 256; i++)
		keys[i] = false;
}

Input::~Input()
{
}

bool Input::IsKeyDown(UINT key)
{
	return keys[key];
}

void Input::KeyDown(UINT key)
{
	keys[key] = true;
}

void Input::KeyUp(UINT key)
{
	keys[key] = false;
}