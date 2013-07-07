#include "TheEntireActualGraphics.h"


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

	playerGraphics->SetModel(playerModel);

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

	delete [] playerModel.indices;
	delete [] playerModel.vertices;
}

void TheEntireActualGraphics::Render(ID3D11DeviceContext* context, D3DXMATRIX transMatrix)
{
	playerGraphics->Render(context, transMatrix);
	enemyGraphics->Render(context, transMatrix);
}