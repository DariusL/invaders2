#include "includes.h"
#include "AppHandle.h"

App *AppHandle::handle;
AppHandle::AppHandle(App *handle)
{
	AppHandle::handle = handle;
}


AppHandle::~AppHandle()
{
}
