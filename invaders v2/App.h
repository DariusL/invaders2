#pragma once
#include <Windows.h>
#include "Globals.h"
#include "Graphics.h"
#include "Input.h"
#include "World.h"
#include "Logger.h"
#include "ResourceManager.h"

class Graphics;
class App
{
	Graphics *graphics;
	Input *input;
	World *world;
	Logger *logger;
	ResourceManager *manager;

	HWND wHandle;
	HINSTANCE hInstance;
	LPCWSTR appName;

	int screenHeight;
	int screenWidth;
	int frameRate;

	bool fullscreen;
public:
	App(void);
	~App(void);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	bool Init();
	void Run();

	void GetScreenDims(int &width, int &heigth){width = screenWidth; heigth = screenHeight;}

	HWND GetWindowHandle(){return wHandle;}
	Logger *GetLogger(){return logger;}
	ResourceManager *GetResourceManager(){return manager;}

	static App *Get(){return Handle;}
private:
	void InitWindows();
	void ShutdownWindows();
	bool OnLoop();
	static App *Handle;
};

static LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l){return App::Get()->MessageHandler(h, u, w, l);}