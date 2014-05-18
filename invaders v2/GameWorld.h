#include "includes.h"
#include "MenuItem.h"
#include "Grid.h"
#include "BulletList.h"
#include "Collider.h"
#include "ColorDrawableEntity.h"
#include "Observers.h"

class GameWorld : public IDrawable
{
	const e::XMFLOAT2 size = e::XMFLOAT2(20.0f, 30.0f);
	e::shared_ptr<ColorDrawableEntity> player;
	BulletList playerBullets;
	e::XMFLOAT3 pos;
	Collider collider;
	Grid enemies;
	ulong difficulty;
	e::vector<UpgradeObservers::ObserverScopeRef> or;
public:
	GameWorld(ID3D11Device *device, e::XMVECTOR pos);
	void Loop(InputType input, int frame);
	void Render(RenderParams &params);
	e::unordered_map<int, int> GetPlayerData();
private:
	void OnEnemyDeath(const e::shared_ptr<GameEntity> enemy);
};