#include "includes.h"
#include "App.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	App app;
	if(!app.Init())
		return 1;

	app.Run();

	return 0;
}