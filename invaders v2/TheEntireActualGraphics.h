#pragma once
#include "AbstractGroupGraphics.h"
#include "PlayerGraphics.h"
#include "EnemyGridGraphics.h"
#include "Model.h"

class TheEntireActualGraphics : public AbstractGroupGraphics
{
public:
	bool Init(ID3D11Device*, World*, HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
public:
	TheEntireActualGraphics(void);
	~TheEntireActualGraphics(void);

protected:
	PlayerGraphics *playerGraphics;
	EnemyGridGraphics *enemyGraphics;
	Model playerModel;
};