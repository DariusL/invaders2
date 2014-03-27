#pragma once
#include "includes.h"
#include "ColorDrawableEntity.h"
#include "MenuItem.h"

class Attribute : public IDrawableObject, public MenuItem
{
	float width;
	e::XMFLOAT3 pos;
protected:
	ColorDrawableEntity name, value;
public:
	Attribute(e::XMVECTOR pos, e::string text, float width, e::XMFLOAT4 color, ColorDrawableEntity &&value, float scale = 1.0f);
	virtual bool Loop() = 0;
	virtual void Delay() = 0;
	virtual void Select(bool selected) = 0;	
	virtual void Render(const RenderParams&) = 0;
protected:
	virtual bool Update(ID3D11DeviceContext *context) = 0;
	e::XMVECTOR ValuePos(float valueWidth);
	e::XMVECTOR NamePos(float nameWidth);
};