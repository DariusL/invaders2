#pragma once
#include "includes.h"
#include "Globals.h"
using namespace std;
class Window
{
	HWND windowHandle;
	bool fullscreen;
	wstring appName;
	HINSTANCE hInstance;
	uint width, height;
public:
	Window(uint width, uint height, bool fullscreen, wstring appName);
	~Window();

	HWND GetWindowHandle(){ return windowHandle; }
};

