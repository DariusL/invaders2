#include <Windows.h>
#include "App.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Logger *l = new Logger();
	l->Init();
	logger = l;

	App *app = new App();
	if(!app->Init())
		return 1;

	app->Run();
	l->Shutdown();

	return 0;
}