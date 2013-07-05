#include "EnemyGridGraphics.h"


EnemyGridGraphics::EnemyGridGraphics(void)
{
}


EnemyGridGraphics::~EnemyGridGraphics(void)
{
}

bool EnemyGridGraphics::Init(ID3D11Device* device, World* world, HWND hwnd)
{
	int width = world->GetEnemies()->GetWidth();
	int height = world->GetEnemies()->GetWidth();

	this->world = world;

	playerModel.vertexCount = 4;
	playerModel.vertices = new VertexType[playerModel.vertexCount];
	playerModel.indexCount = 6;
	playerModel.indices = new int[playerModel.indexCount];	
	
	playerModel.vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	playerModel.vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	playerModel.vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	playerModel.vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	playerModel.vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	playerModel.vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);

	playerModel.vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	playerModel.vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	playerModel.indices[0] = 1;
	playerModel.indices[1] = 2;
	playerModel.indices[2] = 0;

	playerModel.indices[3] = 1;
	playerModel.indices[4] = 3;
	playerModel.indices[5] = 2;

	for(int i = 0; i < width*height; i++)
	{
		enemyGraphics.push_back(make_shared<EnemyGraphics>());
		enemyGraphics[i]->SetModel(playerModel);
		enemyGraphics[i]->setIndex(i);
		if(!enemyGraphics[i]->Init(device, world, hwnd))
			return false;
	}

	return true;
}

void EnemyGridGraphics::Shutdown()
{
	int width = world->GetEnemies()->GetWidth();
	int height = world->GetEnemies()->GetWidth();

	for(int i = 0; i < width*height; i++)
	{
		enemyGraphics[i]->Shutdown();
	}

	delete [] playerModel.indices;
	delete [] playerModel.vertices;
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