#pragma once
#include "Globals.h"

using namespace Microsoft::WRL;

class IDrawable
{
public:
	IDrawable(){}
	IDrawable(IDrawable&&){}

	IDrawable(IDrawable&) = delete;
	IDrawable &operator=(IDrawable&) = delete;

	virtual void Init(ComPtr<ID3D11Device>) = 0;
	virtual void Render(const RenderParams&) = 0;
};