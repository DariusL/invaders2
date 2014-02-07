#include "includes.h"
#include "Input.h"
#include "Globals.h"

Input *Input::handle;

Input::Input(void)
{
	handle = this;
	e::fill(keys, keys + 255, false);
}

Input::~Input()
{
}

bool Input::IsKeyDown(int key)
{
	return handle->keys[key];
}

void Input::KeyDown(int key)
{
	keys[key] = true;
}

void Input::KeyUp(int key)
{
	keys[key] = false;
}