#pragma once
#include "includes.h"
#include "Screen.h"
#include "Button.h"
#include "MenuList.h"
#include "ColorDrawableEntity.h"

class MenuScreen : public Screen
{
	static const e::XMFLOAT3 HEADER_POS;
	static const e::XMFLOAT3 FIRST_ITEM_POS;
	static const e::XMFLOAT3 ITEM_OFF;
	static const e::XMFLOAT3 FOOTER_POS;

	ColorDrawableEntity header;
	PressRegister backRegister;
	bool close;
public:
	MenuScreen(e::XMVECTOR pos, e::string header);
protected:
	MenuList items;
	virtual void RenderInternal(RenderParams &params);
	virtual int LoopInternal(InputType input, int frame);
	virtual void DelayInternal();
	virtual void Close(){ close = true; }

	template<class T>
	void Add(e::unique_ptr<T> &&item)
	{
		items.Add(move(item));
	}
};