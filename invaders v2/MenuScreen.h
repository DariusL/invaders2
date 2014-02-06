#pragma once
#include "includes.h"
#include "Screen.h"
#include "DrawableEntity.h"
#include "Button.h"

class MenuScreen : public Screen
{
	static const e::XMFLOAT3 HEADER_POS;
	static const e::XMFLOAT3 FIRST_ITEM_POS;
	static const e::XMFLOAT3 ITEM_OFF;
	static const e::XMFLOAT3 FOOTER_POS;

	vector<e::unique_ptr<MenuItem>> items;
	SimpleDrawableEntity header;
	int selected;
	InputRegister backRegister;
public:
	MenuScreen(e::XMVECTOR pos, e::string header);
protected:
	virtual void RenderInternal(const RenderParams &params);
	virtual int LoopInternal(int input, float frame);
	e::XMVECTOR GetNextItemPos();
};