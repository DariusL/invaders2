#pragma once
#include "includes.h"
#include "Screen.h"
#include "DrawableEntity.h"
#include "Button.h"
#include "MenuList.h"

class MenuScreen : public Screen
{
	static const e::XMFLOAT3 HEADER_POS;
	static const e::XMFLOAT3 FIRST_ITEM_POS;
	static const e::XMFLOAT3 ITEM_OFF;
	static const e::XMFLOAT3 FOOTER_POS;

	MenuList items;
	SimpleDrawableEntity header;
	InputRegister backRegister;
public:
	MenuScreen(e::XMVECTOR pos, e::string header);
protected:
	virtual void RenderInternal(const RenderParams &params);
	virtual int LoopInternal(int input, float frame);
	virtual void DelayInternal();
};