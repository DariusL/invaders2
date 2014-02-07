#include "includes.h"
#include "MenuList.h"
using namespace e;

MenuList::MenuList(e::XMFLOAT3 startPos, e::XMFLOAT3 offset, int nextKey, int prevKey)
:startPos(startPos), offset(offset), selected(0), next(nextKey), prev(prevKey)
{
}

bool MenuList::Loop()
{
	bool handled = false;
	try
	{
		if (items.at(this->selected)->Loop())
			handled = true;
	}
	catch (out_of_range o){}
	if (selected > 0 && prev.IsDown() && !handled)
	{
		handled = true;
		if (prev.Register())
		{
			SetSelection(selected - 1);
		}
	}
	if (selected < items.size() - 1 && next.IsDown() && !handled)
	{
		handled = true;
		if (next.Register())
		{
			SetSelection(selected + 1);
		}
	}

	return handled;
}

void MenuList::Delay()
{
	for (auto &item : items)
		item->Delay();
}

void MenuList::Render(const RenderParams &params)
{
	for (auto &item : items)
		item->Render(params);
}

e::XMVECTOR MenuList::GetNextItemPos()
{
	return XMLoadFloat3(&this->startPos) + XMLoadFloat3(&this->offset) * (float)items.size();
}

void MenuList::SetSelection(int selected)
{
	items[this->selected]->Select(false);
	items[selected]->Select(true);
	this->selected = selected;
}

void MenuList::Select(bool selected)
{
	try
	{
		items.at(this->selected)->Select(selected);
	}
	catch (out_of_range o){}
}