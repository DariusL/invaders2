#pragma once
#include "includes.h"
#include "MenuItem.h"
#include "HoldRegister.h"

class MenuList : public MenuItem
{
	e::vector<e::unique_ptr<MenuItem>> items;
	e::XMFLOAT3 pos;
	e::XMFLOAT3 offset;
	uint show, first;
	uint selected;
	HoldRegister next, prev;
public:
	MenuList(e::XMVECTOR pos, e::XMFLOAT3 offset, uint show, Input::ACTION nextKey = Input::ACTION_DOWN, Input::ACTION prevKey = Input::ACTION_UP);
	bool Loop(InputType input);
	void Delay();
	void Render(const RenderParams &params);
	void SetSelection(int selected);
	void Select(bool selected);
	template<class T>
	void Add(e::unique_ptr<T> &&item);
	void MoveTo(e::XMVECTOR pos);
protected:
	void Reposition();
};

template<class T>
void MenuList::Add(e::unique_ptr<T> &&item)
{
	items.push_back(move(item));
	SetSelection(this->selected);
	Reposition();
}