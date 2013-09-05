#include "App.h"

App *App::Handle;

App::App()
{
	/*graphics = NULL;
	input = NULL;*/

	screenHeight = 720;
	screenWidth = 1280;
	frameRateLimit = 1000;
	fullscreen = false;
	world = NULL;
}

App::~App()
{
	ShutdownWindows();
	if(input)
	{
		delete input;
		input = NULL;
	}
	if(world)
	{
		delete world;
		world = NULL;
	}
	if(logger)
	{
		delete logger;
		logger = NULL;
	}
	if(manager)
	{
		delete manager;
		manager = NULL;
	}
}

bool App::Init()
{
	InitWindows();
	Handle = this;

	manager = new ResourceManager();
	if(!manager->Init())
		return false;

	world = new World();

	input = new Input();
	if(!input)
		return false;

	if(!graphics.Init(screenWidth, screenHeight, wHandle, fullscreen, 1.0f))
		return false;

	logger = new Logger();
	if(!logger->Init())
		return false;

	return true;
}

void App::InitWindows()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	hInstance = GetModuleHandle(NULL);

	appName = L"DX framework";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = MsgRedirect;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = appName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	if(fullscreen)
	{
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);
		ZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	wHandle = CreateWindowEx(WS_EX_APPWINDOW, appName, appName, 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, hInstance, NULL);
	ShowWindow(wHandle, SW_SHOW);
	SetForegroundWindow(wHandle);
	SetFocus(wHandle);
	ShowCursor(false);
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
		graphics.Render();
	}
}

bool App::OnLoop()
{
	if(!world->IsStarted())
	{
		world->Start(manager->GetLevel(ResourceManager::Levels::L1));
		if(!graphics.Init(world))
			return false;
	}
	int worldEvents = 0;
	if(input->IsKeyDown(VK_LEFT))
		worldEvents |= ControlCodes::LEFT;
	if(input->IsKeyDown(VK_RIGHT))
		worldEvents |= ControlCodes::RIGHT;
	if(input->IsKeyDown(VK_SPACE))
		worldEvents |= ControlCodes::FIRE;
	if(input->IsKeyDown(VK_ESCAPE))
		Quit();
	if(input->IsKeyDown(VK_DOWN))
		graphics.ChangeBrightness(-0.001f);
	if(input->IsKeyDown(VK_UP))
		graphics.ChangeBrightness(0.001f);

	int worldResult = world->OnLoop(worldEvents, (clock() - lastFrame) / float(CLOCKS_PER_SEC));
	lastFrame = clock();
	switch (worldResult)
	{
	case World::Result::GAME_OVER:
		return false;
	case World::Result::NEXT_LEVEL:
		world->Stop();
		break;
	}
	return true;
}

void App::Quit()
{
	running = false;
}

void App::ShutdownWindows()
{
	ShowCursor(true);
	if(fullscreen)
		ChangeDisplaySettings(NULL, 0);
	DestroyWindow(wHandle);
	wHandle = NULL;
	UnregisterClass(appName, hInstance);
	hInstance = NULL;
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
		input->KeyDown(wparam);
		break;
	case WM_KEYUP:
		input->KeyUp(wparam);
		break;
	default:
		return DefWindowProc(whandle, message, wparam, lparam);
	}
	return 0;
}