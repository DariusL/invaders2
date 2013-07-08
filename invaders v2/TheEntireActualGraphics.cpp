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
	playerGraphics = new PlayerGraphics();
	enemyGraphics = new EnemyGridGraphics();

	playerGraphics->SetModel(((App*)App::Get())->GetResourceManager()->GetModel(ResourceManager::ModelCodes::PLAYER));

	if(!playerGraphics->Init(device, world, hwnd))
		return false;

	if(!enemyGraphics->Init(device, world, hwnd))
		return false;

	return true;
}

void TheEntireActualGraphics::Shutdown()
{
	if(playerGraphics != NULL)
	{
		playerGraphics->Shutdown();
		playerGraphics = NULL;
	}

	if(enemyGraphics != NULL)
	{
	
		enemyGraphics->Shutdown();
		enemyGraphics = NULL;
	}
}

void TheEntireActualGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	playerGraphics->Render(context, transMatrix);
	enemyGraphics->Render(context, transMatrix);
}