#pragma once
#include <Windows.h>
#include "Globals.h"
#include "Graphics.h"
#include "Input.h"
#include "World.h"
#include "Logger.h"

class Graphics;
class App
{
public:
	App(void);
	~App(void){}

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	bool Init();
	void Shutdown();
	void Run();

	void getScreenDims(int &width, int &heigth){width = screenWidth; heigth = screenHeight;}
	HWND getWindowHandle(){return wHandle;}
private:
	void InitWindows();
	void ShutdownWindows();
	bool OnLoop();
private:
	Graphics *graphics;
	Input *input;
	World *world;

	HWND wHandle;
	HINSTANCE hInstance;
	LPCWSTR appName;

	int screenHeight;
	int screenWidth;
	int frameRate;

	bool fullscreen;
};

static LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l){return ((App*)AppHandle)->MessageHandler(h, u, w, l);}