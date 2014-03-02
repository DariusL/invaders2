#include "includes.h"
#include "MenuItem.h"
#include "DrawableShooter.h"
#include "Grid.h"
#include "BulletList.h"

class GameWorld : public IDrawable
{
	const e::XMFLOAT2 size = e::XMFLOAT2(20.0f, 30.0f);
	DrawableShooter player;
	BulletList playerBullets;
	XMFLOAT3 pos;
	Grid enemies;
public:
	GameWorld(ID3D11Device *device, e::XMVECTOR pos);
	void Loop(int frame);
	void Render(const RenderParams &params);
};