#pragma once
#pragma warning(disable : 4005)
#include <d3d11.h>
#include <D3DX10math.h>
#include "World.h"
#include "Model.h"

class GraphicsObject 
{
public:
	virtual bool Init(ID3D11Device*, World*, HWND) = 0;
	virtual void Shutdown() = 0;
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX) = 0;

protected:
	virtual bool InitBuffers(ID3D11Device*) = 0;
	virtual void ShutdownBuffers() = 0;
	virtual void SetBuffers(ID3D11DeviceContext*) = 0;
	virtual void Update(ID3D11DeviceContext*) = 0;

	World *world;
};