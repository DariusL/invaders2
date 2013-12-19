#pragma once

class App;
class AppHandle
{
	static App* handle;
public:
	AppHandle(App *handle);
	~AppHandle();
	static App &Get(){ return *handle; }
};

