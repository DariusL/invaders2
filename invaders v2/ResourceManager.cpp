#include "ResourceManager.h"


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
		return make_shared<Shooter>(hitboxes[Hitboxes::HITBOX_ENEMY], 0.0f, 0.5f, models[Models::MODEL_ENEMY]);
		break;
	default:
		return NULL;
		break;
	}
}

bool ResourceManager::Init()
{
	Model *temp;
	temp = new Model;
	
	temp->vertexCount = 4;
	temp->vertices = unique_ptr<VertexType[]>(new VertexType[temp->vertexCount]);
	temp->indexCount = 6;
	temp->indices = unique_ptr<int[]>(new int[temp->indexCount]);	
	
	temp->vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	temp->vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	temp->vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	temp->vertices[1].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	temp->vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	temp->vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	temp->vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	temp->vertices[3].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	temp->indices[0] = 1;
	temp->indices[1] = 2;
	temp->indices[2] = 0;

	temp->indices[3] = 1;
	temp->indices[4] = 3;
	temp->indices[5] = 2;

	models.push_back(unique_ptr<Model>(temp));

	temp = new Model;

	temp->vertexCount = 4;
	temp->vertices = unique_ptr<VertexType[]>(new VertexType[temp->vertexCount]);
	temp->indexCount = 6;
	temp->indices = unique_ptr<int[]>(new int[temp->indexCount]);	
	
	temp->vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	temp->vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	temp->vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	temp->vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	temp->vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->indices[0] = 1;
	temp->indices[1] = 2;
	temp->indices[2] = 0;

	temp->indices[3] = 1;
	temp->indices[4] = 3;
	temp->indices[5] = 2;

	models.push_back(unique_ptr<Model>(temp));

	temp = new Model;

	temp->vertexCount = 4;
	temp->vertices = unique_ptr<VertexType[]>(new VertexType[temp->vertexCount]);
	temp->indexCount = 6;
	temp->indices = unique_ptr<int[]>(new int[temp->indexCount]);	
	
	temp->vertices[0].position = D3DXVECTOR3(-0.1f, -0.75f, 0.0f);  // Bottom left.
	temp->vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[1].position = D3DXVECTOR3(-0.1f, 0.75f, 0.0f);  // Top left
	temp->vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[2].position = D3DXVECTOR3(0.1f, -0.75f, 0.0f);  // Bottom right.
	temp->vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->vertices[3].position = D3DXVECTOR3(0.1f, 0.75f, 0.0f);  // Top right.
	temp->vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	temp->indices[0] = 1;
	temp->indices[1] = 2;
	temp->indices[2] = 0;

	temp->indices[3] = 1;
	temp->indices[4] = 3;
	temp->indices[5] = 2;

	models.push_back(unique_ptr<Model>(temp));

	hitboxes.push_back(D3DXVECTOR2(2.0f, 2.0f));
	hitboxes.push_back(D3DXVECTOR2(2.0f, 2.0f));
	hitboxes.push_back(D3DXVECTOR2(0.2f, 1.5f));
	hitboxes.push_back(D3DXVECTOR2(1.0f, 1.0f));

	return true;
}