#pragma once
#include <d3d11.h>
#include <D3DX10math.h>
#include <wrl\client.h>
#include "Globals.h"
using namespace Microsoft::WRL;
class IDrawable
{
public:
	virtual bool Init(ComPtr<ID3D11Device>) = 0;
	virtual void Render(RenderParams) = 0;
};