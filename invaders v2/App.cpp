#include "includes.h"
#include "App.h"
#include "ResourceManager.h"
#include "TestScene.h"
#include "MainMenu.h"
#include "AudioManager.h"
#include "LoggerManager.h"
#include "DebugLoggerFactory.h"
#include "LoggerFactory.h"
#include "KennyLogginsFactory.h"

App::App(uint width, uint height, bool fullscreen, wstring name, int tick)
:screenHeight(height), screenWidth(width), fullscreen(fullscreen), appName(name),
window(width, height, fullscreen, name), wHandle(window.GetWindowHandle()),
graphics(width, height, window.GetWindowHandle(), fullscreen), handle(this),
settings(L"settings"),
tick(tick)
{
	world = make_unique<MainMenu>(e::XMLoadFloat3(&ZeroVec3));
	AudioManager::PlayNextSong();
	Log<DebugLoggerFactory, LoggerFactory, KennyLogginsFactory>("App created");
}

App::~App()
{
	Log<DebugLoggerFactory, LoggerFactory, KennyLogginsFactory>("App destroyed");
}

void App::Run()
{
	MSG msg;
	running = true;
	ZeroMemory(&msg, sizeof(msg));
	lastFrame = clock();

	while(running)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(!OnLoop())
		{
			running = false;
			break;
		}
	}
}

bool App::OnLoop()
{
	auto &actions = input.Loop();
	int frame = (int)(clock() - lastFrame);
	e::string str = e::to_string(frame) + "\n";
	//OutputDebugStringA(str.c_str());
	int worldResult = world->Loop(actions, frame);
	lastFrame += frame;
	switch (worldResult)
	{
	case RESULT_CLOSE:
		return false;
	}
	graphics.Render(*world); 
	return true;
}

void App::Quit()
{
	running = false;
}

LRESULT CALLBACK App::MessageHandler(HWND whandle, UINT message , WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		Quit();
		break;
	case WM_QUIT:
		Quit();
		break;
	case WM_KEYDOWN:
		input.KeyDown(wparam);
		break;
	case WM_KEYUP:
		input.KeyUp(wparam);
		break;
	default:
		return DefWindowProc(whandle, message, wparam, lparam);
	}
	return 0;
}