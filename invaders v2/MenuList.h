#pragma once
#include "includes.h"
#include "MenuItem.h"
#include "HoldRegister.h"

class MenuList : public MenuItem
{
	e::vector<e::unique_ptr<MenuItem>> items;
	e::XMFLOAT3 startPos;
	e::XMFLOAT3 offset;
	uint selected;
	HoldRegister next, prev;
public:
	MenuList(e::XMFLOAT3 startPos, e::XMFLOAT3 offset, Input::ACTION nextKey = Input::ACTION_DOWN, Input::ACTION prevKey = Input::ACTION_UP);
	bool Loop(InputType input);
	void Delay();
	void Render(const RenderParams &params);
	e::XMVECTOR GetNextItemPos();
	void SetSelection(int selected);
	void Select(bool selected);
	template<class T>
	void Add(e::unique_ptr<T> &&item);
};

template<class T>
void MenuList::Add(e::unique_ptr<T> &&item)
{
	items.push_back(move(item));
	SetSelection(this->selected);
}