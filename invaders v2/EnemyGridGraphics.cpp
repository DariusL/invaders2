#include "EnemyGridGraphics.h"
#include "App.h"
#include "ResourceManager.h"


EnemyGridGraphics::EnemyGridGraphics(void)
{
}


EnemyGridGraphics::~EnemyGridGraphics(void)
{
	
}

bool EnemyGridGraphics::Init(ID3D11Device* device, World* world, HWND hwnd)
{
	int width = world->GetEnemies()->GetWidth();
	int height = world->GetEnemies()->GetHeight();

	Model *model = ((App*)App::Get())->GetResourceManager()->GetModel(ResourceManager::ModelCodes::MODEL_ENEMY);

	this->world = world;

	for(int i = 0; i < width*height; i++)
	{
		enemyGraphics.push_back(make_shared<EnemyGraphics>());
		enemyGraphics[i]->SetModel(model);
		enemyGraphics[i]->setIndex(i);
		if(!enemyGraphics[i]->Init(device, world, hwnd))
			return false;
	}

	return true;
}

void EnemyGridGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	int width = world->GetEnemies()->GetWidth();
	int height = world->GetEnemies()->GetHeight();

	for(int i = 0; i < width*height; i++)
	{
		enemyGraphics[i]->Render(context, transMatrix);
	}
}