#include <Windows.h>
#include "App.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	App *app = new App();
	if(!app->Init())
		return 1;

	app->Run();
	delete app;

	return 0;
}