#pragma once

#include "Graphics.h"
#include "Scene.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Input.h"

class Graphics;
class App
{
	Graphics graphics;
	Input input;

	unique_ptr<Scene> world;

	ResourceManager manager;

	HWND wHandle;
	HINSTANCE hInstance;
	LPCWSTR appName;

	int screenHeight;
	int screenWidth;
	int frameRateLimit;

	long lastFrame;

	bool fullscreen;
	bool running;
public:
	App(void);
	~App(void);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	void Init();
	void Run();
	void Quit();

	void GetScreenDims(int &width, int &heigth){width = screenWidth; heigth = screenHeight;}

	HWND GetWindowHandle(){return wHandle;}
	IWorld *GetWorld(){return world.get();}

	static App *Get(){return Handle;}
private:
	void InitWindows();
	void ShutdownWindows();
	bool OnLoop();
	static App *Handle;
};

static LRESULT CALLBACK MsgRedirect(HWND h, UINT u, WPARAM w, LPARAM l){return App::Get()->MessageHandler(h, u, w, l);}