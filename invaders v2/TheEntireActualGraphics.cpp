#include "TheEntireActualGraphics.h"
#include "App.h"
#include "ResourceManager.h"


TheEntireActualGraphics::TheEntireActualGraphics(void)
{
	playerGraphics = NULL;
	enemyGraphics = NULL;
}


TheEntireActualGraphics::~TheEntireActualGraphics(void)
{
}

bool TheEntireActualGraphics::Init(ID3D11Device* device, World* world, HWND hwnd)
{
	playerGraphics = unique_ptr<PlayerGraphics>(new PlayerGraphics());
	enemyGraphics = unique_ptr<EnemyGridGraphics>(new EnemyGridGraphics());
	bulletGraphics = unique_ptr<BulletGraphics>(new BulletGraphics());

	playerGraphics->SetModel(App::Get()->GetResourceManager()->GetModel(ResourceManager::ModelCodes::PLAYER));
	bulletGraphics->SetModel(App::Get()->GetResourceManager()->GetModel(ResourceManager::ModelCodes::BULLET));

	if(!playerGraphics->Init(device, world, hwnd))
		return false;

	if(!enemyGraphics->Init(device, world, hwnd))
		return false;

	if(!bulletGraphics->Init(device, world, hwnd))
		return false;

	return true;
}

void TheEntireActualGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	playerGraphics->Render(context, transMatrix);
	enemyGraphics->Render(context, transMatrix);
	bulletGraphics->Render(context, transMatrix);
}