#pragma once

#include "Graphics.h"
#include "Screen.h"
#include "Logger.h"
#include "Input.h"
#include "Window.h"
#include "AppHandle.h"
#include "Settings.h"
#include "AudioManager.h"

class App
{
	AppHandle handle;
	wstring appName;
	bool fullscreen;
	uint screenHeight;
	uint screenWidth;

	Input input;
	Settings settings;
	Window window;
	AudioManager audio;
	Graphics graphics;

	unique_ptr<Screen> world;

	HWND wHandle;
	HINSTANCE hInstance;
	
	long lastFrame;
	int tick;
	bool running;
public:
	App(uint width = 1280, uint height = 720, bool fullscreen = false, wstring name = L"Invaders v2", int tick = 500);
	~App(void);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	void Run();
	void Quit();

	void GetScreenDims(int &width, int &heigth){width = screenWidth; heigth = screenHeight;}

	HWND GetWindowHandle(){return wHandle;}
	bool Tick(){ return (lastFrame % tick) < (tick / 2); }
private:
	bool OnLoop();
};