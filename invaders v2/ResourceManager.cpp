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

	normalModel = GetModelFromOBJ("teapot.obj");
	normalModel->hitbox = D3DXVECTOR2(1.5f, 1.5f);

	return true;
}

unique_ptr<NormalModel> ResourceManager::GetModelFromOBJ(char *filename)
{
	unique_ptr<NormalModel> model = unique_ptr<NormalModel>(new NormalModel());
	ifstream in = ifstream(filename, ios::binary);
	vector<D3DXVECTOR3> normals;
	vector<int> temp;
	string input;
	NormalVertexType vertex;
	float x, y, z;
	if(!in.is_open())
		return NULL;

	while(!in.eof())
	{
		in >> input;

		if(input == "#")
		{
			in.ignore(200, '\n');
			continue;
		}

		if (input == "v")
			{
					in >> x >> y >> z;
					vertex.color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					vertex.normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					vertex.position = D3DXVECTOR3(x, y, -z);
					model->vertices.push_back(vertex);
			}
			else if (input == "vn")
			{
					in >> x >> y >> z;
					normals.emplace_back(x, y, -z);
			}
			else if (input == "f")
			{
					string blob;
					int v, n;
					int index;
					temp.clear();

					for (int i = 0; i < 3; i++)
					{
						in >> blob;
						index = blob.find_first_of('/');
						v = stoi(blob.substr(0, index)) - 1;
						n = stoi(blob.substr(index + 2)) - 1;
						temp.push_back(v);
						model->vertices[v].normal += normals[n];
					}
					for(int i = 2; i >= 0; i--)
						model->indices.push_back(temp[i]);
			}
	}

	return model;
}

bool ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	shaders.push_back(make_shared<ColorShader>());
	shaders.push_back(make_shared<ColorInstancedShader>());
	shaders.push_back(make_shared<GlobalDiffuseShader>());
	shaders.push_back(make_shared<GlobalSpecularShader>());
	for(auto &shader : shaders)
		shader->Init(device);
	return true;
}