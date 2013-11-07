#include "includes.h"
#include "App.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	App app;
	app.Init();

	app.Run();

	return 0;
}