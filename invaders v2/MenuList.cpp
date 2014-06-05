#include "includes.h"
#include "MenuList.h"
#include "Utils.h"
#include "Observers.h"
using namespace e;

MenuList::MenuList(e::XMVECTOR pos, e::XMFLOAT3 offset, uint show, Input::ACTION nextKey, Input::ACTION prevKey)
	:offset(offset), selected(0), next(nextKey), prev(prevKey), show(show), first(0)
{
	e::XMStoreFloat3(&this->pos, pos);
	Reposition();
}

bool MenuList::Loop(InputType input)
{
	bool handled = false;
	try
	{
		if (items.at(this->selected)->Loop(input))
			handled = true;
	}
	catch (out_of_range o){}
	if (selected > 0 && prev.IsDown(input) && !handled)
	{
		handled = true;
		if (prev.Register(input))
		{
			SetSelection(selected - 1);
			MenuObservers::Notify(0);
		}
	}
	if (selected + 1 < items.size() && next.IsDown(input) && !handled)
	{
		handled = true;
		if (next.Register(input))
		{
			SetSelection(selected + 1);
			MenuObservers::Notify(0);
		}
	}

	return handled;
}

void MenuList::Delay()
{
	for (auto &item : items)
		item->Delay();
}

void MenuList::Render(RenderParams &params)
{
	for (uint i = first; i < first + show && i < items.size(); i++)
		items[i]->Render(params);
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

void MenuList::Reposition()
{
	uint count = show > items.size() ? items.size() : show;
	auto off = e::XMLoadFloat3(&offset);
	auto first = e::XMLoadFloat3(&pos);
	first -= off * float(count - 1) / 2.0f;
	for (uint i = this->first; i < this->first + show && i < items.size(); i++)
	{
		items[i]->MoveTo(first);
		first += off;
	}
}

void MenuList::MoveTo(e::XMVECTOR pos)
{
	e::XMStoreFloat3(&this->pos, pos);
	Reposition();
}