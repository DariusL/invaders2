#pragma once
#include "Globals.h"

class IDrawable
{
public:
	IDrawable(){}
	virtual ~IDrawable(){}
	IDrawable(IDrawable&&){}

	IDrawable(IDrawable&) = delete;

	virtual void Render(const RenderParams&) = 0;
};