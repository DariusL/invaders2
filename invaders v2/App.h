#pragma once

#include "Graphics.h"
#include "GameWorld.h"
#include "Logger.h"
#include "Input.h"
#include "Window.h"
#include "AppHandle.h"

class App
{
	AppHandle handle;
	wstring appName;
	bool fullscreen;
	uint screenHeight;
	uint screenWidth;

	Input input;
	Window window;
	Graphics graphics;

	unique_ptr<IWorld> world;

	HWND wHandle;
	HINSTANCE hInstance;
	
	long lastFrame;
	bool running;
public:
	App(uint width = 1280, uint height = 720, bool fullscreen = false, wstring name = L"Invaders v2");
	~App(void);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	void Run();
	void Quit();

	void GetScreenDims(int &width, int &heigth){width = screenWidth; heigth = screenHeight;}

	HWND GetWindowHandle(){return wHandle;}
	IWorld *GetWorld(){return world.get();}
private:
	bool OnLoop();
};