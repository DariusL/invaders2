#include "includes.h"
#include "App.h"
#include "Logger.h"
#include "AudioManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	App app;

	app.Run();

	return 0;
}