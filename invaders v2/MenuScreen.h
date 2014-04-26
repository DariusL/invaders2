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

	MenuList items;
	ColorDrawableEntity header;
	PressRegister backRegister;
public:
	MenuScreen(e::XMVECTOR pos, e::string header);
protected:
	virtual void RenderInternal(const RenderParams &params);
	virtual int LoopInternal(InputType input, int frame);
	virtual void DelayInternal();

	template<class T>
	void Add(e::unique_ptr<T> &&item)
	{
		items.Add(move(item));
	}
};