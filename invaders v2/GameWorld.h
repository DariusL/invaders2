#include "includes.h"
#include "MenuItem.h"
#include "Grid.h"
#include "BulletList.h"
#include "Quadtree.h"
#include "Collider.h"
#include "ColorDrawableEntity.h"

class GameWorld : public IDrawable
{
	const e::XMFLOAT2 size = e::XMFLOAT2(20.0f, 30.0f);
	e::shared_ptr<ColorDrawableEntity> player;
	BulletList playerBullets;
	XMFLOAT3 pos;
	Collider collider;
	Grid enemies;
	//Quadtree quadtree;
public:
	GameWorld(ID3D11Device *device, e::XMVECTOR pos);
	void Loop(int frame);
	void Render(const RenderParams &params);
};