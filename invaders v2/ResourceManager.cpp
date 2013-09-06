#include "ResourceManager.h"
using namespace Microsoft::WRL;

ResourceManager::ResourceManager(void)
{
}


ResourceManager::~ResourceManager(void)
{
}

shared_ptr<Shooter> ResourceManager::GetEnemy(int type)
{
	switch (type)
	{
	case Enemies::BASIC:
		return make_shared<Shooter>(hitboxes[Hitboxes::HITBOX_ENEMY], 15.0f, 0.5f, models[Models::MODEL_ENEMY]);
		break;
	default:
		return NULL;
		break;
	}
}

bool ResourceManager::Init()
{
	shared_ptr<Model> temp = make_shared<Model>();
	
	temp->vertexCount = 4;
	temp->indexCount = 6;

	VertexType vertex;
	
	vertex.position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	temp->indices.push_back(1);
	temp->indices.push_back(2);
	temp->indices.push_back(0);

	temp->indices.push_back(1);
	temp->indices.push_back(3);
	temp->indices.push_back(2);

	models.push_back(temp);

	temp = make_shared<Model>();

	temp->vertexCount = 4;
	temp->indexCount = 6;
	
	vertex.position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	temp->indices.push_back(1);
	temp->indices.push_back(2);
	temp->indices.push_back(0);

	temp->indices.push_back(1);
	temp->indices.push_back(3);
	temp->indices.push_back(2);

	models.push_back(temp);

	temp = make_shared<Model>();

	temp->vertexCount = 4;
	temp->indexCount = 6;
	
	vertex.position = D3DXVECTOR3(-0.1f, -0.75f, 0.0f);  // Bottom left.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-0.1f, 0.75f, 0.0f);  // Top left
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.1f, -0.75f, 0.0f);  // Bottom right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.1f, 0.75f, 0.0f);  // Top right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	temp->vertices.push_back(vertex);

	temp->indices.push_back(1);
	temp->indices.push_back(2);
	temp->indices.push_back(0);

	temp->indices.push_back(1);
	temp->indices.push_back(3);
	temp->indices.push_back(2);

	models.push_back(temp);

	hitboxes.push_back(D3DXVECTOR2(2.0f, 2.0f));
	hitboxes.push_back(D3DXVECTOR2(2.0f, 2.0f));
	hitboxes.push_back(D3DXVECTOR2(0.2f, 1.5f));
	hitboxes.push_back(D3DXVECTOR2(1.0f, 1.0f));

	Level *level = new Level();

	level->gridWidth = 11;
	level->gridHeight = 5;
	level->gap = D3DXVECTOR2(3.0f, 3.0f);

	for(int i = 0; i < level->gridHeight * level->gridWidth; i++)
	{
		level->enemies.push_back(Enemies::BASIC);
	}

	levels.push_back(shared_ptr<Level>(level));

	return true;
}

bool ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	colorShader = make_shared<ColorShader>();
	colorInstancedShader = make_shared<ColorInstancedShader>();
	if(!colorShader->Init(device))
		return false;
	if(!colorInstancedShader->Init(device))
		return false;
	return true;
}