#pragma once

#include "Graphics.h"
#include "GameWorld.h"
#include "Scene.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Input.h"
#include "Window.h"

class Graphics;
class App
{
	Graphics graphics;
	Input input;
	Window window;

	unique_ptr<Scene> world;

	ResourceManager manager;

	HWND wHandle;
	HINSTANCE hInstance;
	wstring appName;

	uint screenHeight;
	uint screenWidth;

	long lastFrame;

	bool fullscreen;
	bool running;
public:
	App(uint width = 1280, uint height = 720, bool fullscreen = false, wstring name = L"Invaders v2");
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