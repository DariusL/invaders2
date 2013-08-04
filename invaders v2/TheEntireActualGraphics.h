#pragma once
#include "AbstractGroupGraphics.h"
#include "PlayerGraphics.h"
#include "EnemyGridGraphics.h"
#include "BulletGraphics.h"
#include "EnemyBulletGraphics.h"
#include "Model.h"

class TheEntireActualGraphics : public AbstractGroupGraphics
{
public:
	bool Init(ID3D11Device*, World*, HWND);
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
public:
	TheEntireActualGraphics(void);
	~TheEntireActualGraphics(void);

protected:
	unique_ptr<PlayerGraphics> playerGraphics;
	unique_ptr<EnemyGridGraphics> enemyGraphics;
	unique_ptr<BulletGraphics> bulletGraphics;
	unique_ptr<EnemyBulletGraphics> enemyBullets;
};