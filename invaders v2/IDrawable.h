#pragma once
#include <d3d11.h>
#include <D3DX10math.h>
class IDrawable
{
public:
	virtual bool Init(ID3D11Device*, HWND) = 0;
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX) = 0;
};