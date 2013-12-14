#pragma once
#include "Globals.h"

using namespace Microsoft::WRL;

class IDrawable
{
public:
	IDrawable(){}
	IDrawable(IDrawable&&){}

	IDrawable(IDrawable&) = delete;

	virtual void Init(ComPtr<ID3D11Device>) = 0;
	virtual void Render(RenderParams&) = 0;
};