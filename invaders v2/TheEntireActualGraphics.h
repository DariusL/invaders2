#pragma once
#include "graphicsobject.h"
#include "PlayerGraphics.h"
#include "TestGraphics.h"
#include "Model.h"

class TheEntireActualGraphics : public GraphicsObject
{
public:
	bool Init(ID3D11Device*, World*, HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, D3DXMATRIX);

protected:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	void Update(ID3D11DeviceContext*);
public:
	TheEntireActualGraphics(void);
	~TheEntireActualGraphics(void);

private:
	PlayerGraphics *playerGraphics;
	TestGraphics *test;
	Model playerModel;
};