#pragma once
#include <d3d11.h>
#include <D3DX10math.h>
#include "Globals.h"
class IDrawable
{
public:
	virtual bool Init(ID3D11Device*) = 0;
	virtual void Render(RenderParams) = 0;
};