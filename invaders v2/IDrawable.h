#pragma once
#include <d3d11.h>
#include <D3DX10math.h>
#include <wrl\client.h>
#include "Globals.h"

using namespace Microsoft::WRL;

class IDrawable : public NonCopyable
{
public:
	IDrawable(){}
	IDrawable(IDrawable&&){}
	IDrawable &operator=(IDrawable&&){}

	virtual bool Init(ComPtr<ID3D11Device>) = 0;
	virtual void Render(const RenderParams&) = 0;
};