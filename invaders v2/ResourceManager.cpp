#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
}


ResourceManager::~ResourceManager(void)
{
}

bool ResourceManager::Init()
{
	modelCount = 2;
	Model *temp;
	temp = new Model;
	
	temp->vertexCount = 4;
	temp->vertices = new VertexType[temp->vertexCount];
	temp->indexCount = 6;
	temp->indices = new int[temp->indexCount];	
	
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

	models.push_back(temp);

	temp = new Model;

	temp->vertexCount = 4;
	temp->vertices = new VertexType[temp->vertexCount];
	temp->indexCount = 6;
	temp->indices = new int[temp->indexCount];	
	
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

	models.push_back(temp);

	return true;
}

void ResourceManager::Shutdown()
{
	for(int i = 0; i < models.size(); i++)
	{
		delete [] models[i]->indices;
		delete [] models[i]->vertices;
		delete models[i];
	}
}