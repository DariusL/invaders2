#pragma once
#include "Globals.h"

using namespace Microsoft::WRL;

class IDrawable
{
public:
	IDrawable(){}
	virtual ~IDrawable(){}
	IDrawable(IDrawable&&){}

	IDrawable(IDrawable&) = delete;

	virtual void Render(RenderParams&) = 0;
};