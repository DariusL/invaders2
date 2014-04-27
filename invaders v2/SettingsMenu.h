#pragma once
#include "MenuScreen.h"
#include "Button.h"
#include "Utils.h"

class SettingsMenu : public MenuScreen
{
public:
	SettingsMenu(e::XMVECTOR pos);
protected:
	virtual int LoopInternal(InputType input, int frame);
private:
	void Ok();
	void Cancel();
};