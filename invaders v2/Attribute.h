#pragma once
#include "includes.h"
#include "ColorDrawableEntity.h"
#include "MenuItem.h"

class Attribute : public MenuItem
{
	float width;
	e::XMFLOAT3 pos;
protected:
	ColorDrawableEntity name;
	e::unique_ptr<ColorDrawableEntity> value;
public:
	Attribute(e::XMVECTOR pos, e::string text, float width, e::unique_ptr<ColorDrawableEntity> value, float scale = 1.0f);
	virtual bool Loop(){ return false; }
	virtual void Delay(){}
	virtual void Select(bool selected);
	virtual void Render(const RenderParams &params);
	void MoveTo(e::XMVECTOR pos);
protected:
	void Reposition();
	e::XMVECTOR ValuePos(float valueWidth);
	e::XMVECTOR NamePos(float nameWidth);
};