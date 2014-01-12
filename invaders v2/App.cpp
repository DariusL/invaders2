#include "includes.h"
#include "App.h"
#include "ResourceManager.h"

App::App(uint width, uint height, bool fullscreen, wstring name)
:screenHeight(height), screenWidth(width), fullscreen(fullscreen), appName(name),
window(width, height, fullscreen, name), wHandle(window.GetWindowHandle()),
graphics(width, height, window.GetWindowHandle(), fullscreen), handle(this)
{
	world = unique_ptr<Scene>(new Scene(graphics.GetDevice()));
	graphics.LoadThings(*world);
}

App::~App()
{
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
	if(!world->IsStarted())
	{
		world->Start(RM::Get().GetLevel(ResourceManager::LEVEL::L1));
	}
	int worldEvents = 0;
	if(input.IsKeyDown(VK_LEFT))
		worldEvents |= ControlCodes::LEFT;
	if(input.IsKeyDown(VK_RIGHT))
		worldEvents |= ControlCodes::RIGHT;
	if(input.IsKeyDown(VK_ESCAPE))
		Quit();
	if(input.IsKeyDown(VK_DOWN))
		worldEvents |= ControlCodes::DOWN;
	if(input.IsKeyDown(VK_UP))
		worldEvents |= ControlCodes::UP;
	if(input.IsKeyDown(VK_ADD))
		worldEvents |= ControlCodes::PLUS;
	if(input.IsKeyDown(VK_SUBTRACT))
		worldEvents |= ControlCodes::MINUS;
	if (input.IsKeyDown('W'))
		worldEvents |= ControlCodes::MOVE_FORWARD;
	if (input.IsKeyDown('S'))
		worldEvents |= ControlCodes::MOVE_BACK;
	if (input.IsKeyDown('A'))
		worldEvents |= ControlCodes::MOVE_LEFT;
	if (input.IsKeyDown('D'))
		worldEvents |= ControlCodes::MOVE_RIGHT;
	if (input.IsKeyDown(VK_SPACE))
		worldEvents |= ControlCodes::MOVE_UP;
	if (input.IsKeyDown(VK_CONTROL))
		worldEvents |= ControlCodes::MOVE_DOWN;
	if (input.IsKeyDown('Q'))
		worldEvents |= ControlCodes::ROLL_LEFT;
	if (input.IsKeyDown('E'))
		worldEvents |= ControlCodes::ROLL_RIGHT;
	if (input.IsKeyDown(VK_F1))
		worldEvents |= ControlCodes::EFFECT_1;
	if (input.IsKeyDown(VK_F2))
		worldEvents |= ControlCodes::EFFECT_2;
	if (input.IsKeyDown(VK_F3))
		worldEvents |= ControlCodes::EFFECT_3;
	if (input.IsKeyDown(VK_F4))
		worldEvents |= ControlCodes::EFFECT_4;

	int worldResult = world->OnLoop(worldEvents, (clock() - lastFrame) / float(CLOCKS_PER_SEC));
	lastFrame = clock();
	switch (worldResult)
	{
	case IWorld::Result::GAME_OVER:
		return false;
	case IWorld::Result::NEXT_LEVEL:
		world->Stop();
		break;
	}
	graphics.Render(*world, worldEvents);
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