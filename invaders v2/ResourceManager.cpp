#include "ResourceManager.h"
using namespace Microsoft::WRL;

ResourceManager::ResourceManager(void)
{
}


ResourceManager::~ResourceManager(void)
{
}

shared_ptr<DrawableShooter> ResourceManager::GetEnemy(int type)
{
	switch (type)
	{
	case Enemies::BASIC:
		return make_shared<DrawableShooter>(15.0f, 0.5f, models[Models::MODEL_ENEMY_BASIC]);
		break;
	case Enemies::LAPTOP:
		return make_shared<DrawableShooter>(15.0f, 0.5f, models[Models::MODEL_ENEMY_LAPTOP]);
	default:
		return NULL;
		break;
	}
}

bool ResourceManager::Init()
{
	//player
	shared_ptr<Model> temp = make_shared<Model>();
	
	temp->vertexCount = 4;
	temp->indexCount = 6;
	temp->hitbox = D3DXVECTOR2(2.0f, 2.0f);

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

	//enemy basic
	temp = make_shared<Model>();

	temp->vertexCount = 4;
	temp->indexCount = 6;
	temp->hitbox = D3DXVECTOR2(2.0f, 2.0f);
	
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

	//bullet
	temp = make_shared<Model>();

	temp->vertexCount = 4;
	temp->indexCount = 6;
	temp->hitbox = D3DXVECTOR2(0.2f, 1.5f);
	
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

	//enemy laptop
	temp = make_shared<Model>();
	temp->hitbox = D3DXVECTOR2(2.0f, 2.0f);

	temp->vertexCount = 4;
	temp->indexCount = 6;

	vertex.position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	temp->indices.push_back(1);
	temp->indices.push_back(2);
	temp->indices.push_back(0);

	temp->indices.push_back(1);
	temp->indices.push_back(3);
	temp->indices.push_back(2);

	models.push_back(temp);

	//wall
	temp = make_shared<Model>();
	temp->hitbox = D3DXVECTOR2(1.0f, 1.0f);

	temp->vertexCount = 4;
	temp->indexCount = 6;
	
	vertex.position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);  // Top left
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);  // Bottom right.
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	vertex.position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);  // Top right.
	vertex.color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);
	temp->vertices.push_back(vertex);

	temp->indices.push_back(1);
	temp->indices.push_back(2);
	temp->indices.push_back(0);

	temp->indices.push_back(1);
	temp->indices.push_back(3);
	temp->indices.push_back(2);

	models.push_back(temp);

	Level *level = new Level();

	level->gridWidth = 11;
	level->gridHeight = 5;
	level->gap = D3DXVECTOR2(3.0f, 3.0f);
	level->enemyTypes = vector<int>();
	level->enemyTypes.push_back(Enemies::BASIC);

	for(int i = 0; i < level->gridHeight * level->gridWidth; i++)
	{
		level->enemies.push_back(Enemies::BASIC);
	}

	levels.push_back(shared_ptr<Level>(level));

	normalModel = make_shared<NormalModel>();

	NormalVertexType nvertex;

	normalModel->vertexCount = 4;
	normalModel->indexCount = 6;
	normalModel->hitbox = D3DXVECTOR2(2.0f, 2.0f);
	
	nvertex.position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	nvertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	nvertex.normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	normalModel->vertices.push_back(nvertex);

	nvertex.position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left
	nvertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	nvertex.normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	normalModel->vertices.push_back(nvertex);

	nvertex.position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	nvertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	nvertex.normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	normalModel->vertices.push_back(nvertex);

	nvertex.position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	nvertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	nvertex.normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	normalModel->vertices.push_back(nvertex);

	normalModel->indices.push_back(1);
	normalModel->indices.push_back(2);
	normalModel->indices.push_back(0);

	normalModel->indices.push_back(1);
	normalModel->indices.push_back(3);
	normalModel->indices.push_back(2);

	return true;
}

bool ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	shaders.push_back(make_shared<ColorShader>());
	shaders.push_back(make_shared<ColorInstancedShader>());
	shaders.push_back(make_shared<GlobalDiffuseShader>());
	for(auto &shader : shaders)
		shader->Init(device);
	return true;
}