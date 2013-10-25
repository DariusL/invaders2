#include "includes.h"
#include "ResourceManager.h"
#include "ColorInstancedShader.h"
#include "ColorShader.h"
#include "GlobalDiffuseShader.h"
#include "GlobalSpecularShader.h"
#include "PointDiffuseShader.h"
#include "PointSpecularShader.h"
#include "TextureShader.h"
#include "NormalMappedShader.h"
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
	auto tempObj = GetModelFromOBJ("ball.obj");
	tempObj->hitbox = D3DXVECTOR2(2.0f, 2.0f);
	models.push_back(move(tempObj));

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

	normalModel = GetNormalModelFromOBJ("teapot.obj");
	normalModel->hitbox = D3DXVECTOR2(1.5f, 1.5f);

	texturedModel = GetTexturedModelFromOBJ("textured_ball.obj");
	normalModel->hitbox = D3DXVECTOR2(2.0f, 2.0f);

	return true;
}

unique_ptr<Model> ResourceManager::GetModelFromOBJ(char *filename)
{
	auto normalModel = GetNormalModelFromOBJ(filename);
	auto ret = unique_ptr<Model>(new Model());
	VertexType vertex;
	ret->hitbox = normalModel->hitbox;
	ret->indices = normalModel->indices;
	for(NormalVertexType normalVertex : normalModel->vertices)
	{
		vertex.color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex.position = normalVertex.position;
		ret->vertices.push_back(vertex);
	}
	return ret;
}

unique_ptr<NormalModel> ResourceManager::GetNormalModelFromOBJ(char *filename)
{
	auto model = unique_ptr<NormalModel>(new NormalModel());
	ifstream in(filename, ios::binary);
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

unique_ptr<TexturedNormalModel> ResourceManager::GetTexturedModelFromOBJ(char *filename)
{
	auto model = unique_ptr<TexturedNormalModel>(new TexturedNormalModel());
	ifstream in(filename, ios::binary);
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> tex;
	vector<int> temp;
	string input;
	NormalMappedVertexType vertex;
	D3DXVECTOR3 binormal, tangent;
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
				vertex.color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
				vertex.position = D3DXVECTOR3(x, y, -z);
				vertex.tangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vertex.binormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				model->vertices.push_back(vertex);
		}
		else if (input == "vn")
		{
				in >> x >> y >> z;
				normals.emplace_back(x, y, -z);
		}
		else if (input == "vt")
		{
				in >> x >> y >> z;
				tex.emplace_back(x, y);
		}
		else if (input == "f")
		{
				string blob;
				int v, n, t;
				int index, index2;
				temp.clear();

				for (int i = 0; i < 3; i++)
				{
					in >> blob;
					index = blob.find_first_of('/');
					v = stoi(blob.substr(0, index)) - 1;
					index2 = blob.find_first_of('/', index + 1);
					t = stoi(blob.substr(index + 1, index2)) - 1;
					n = stoi(blob.substr(index2 + 1)) - 1;
					temp.push_back(v);
					model->vertices[v].normal = normals[n];
					model->vertices[v].tex = tex[t];
				}
				reverse(temp.begin(), temp.end());
				CalculateTangentAndBinormal(temp, model->vertices);
				model->indices.insert(model->indices.end(), temp.begin(), temp.end());
		}
	}

	return model;
}

void ResourceManager::CalculateTangentAndBinormal(const vector<int> &ind, vector<NormalMappedVertexType> &v)
{
	auto &v1 = v[ind[0]];
	auto &v2 = v[ind[1]];
	auto &v3 = v[ind[2]];

	D3DXVECTOR2 tu(v2.tex.x - v1.tex.x, v3.tex.x - v1.tex.x);
	D3DXVECTOR2 tv(v2.tex.y - v1.tex.y, v3.tex.y - v1.tex.y);

	D3DXVECTOR3 edge1(v2.position - v1.position);
	D3DXVECTOR3 edge2(v3.position - v1.position);

	float den = 1.0f / (tu.x * tv.y - tu.y * tv.x);

	D3DXVECTOR3 tangent((tv.y * edge1 - tv.x * edge2) * den);
	D3DXVECTOR3 binormal((tu.x * edge2 - tv.y * edge1) * den);

	D3DXVec3Normalize(&tangent, &tangent);
	D3DXVec3Normalize(&binormal, &binormal);

	v1.binormal += binormal;
	v1.tangent += tangent;

	v2.binormal += binormal;
	v2.tangent += tangent;

	v3.binormal += binormal;
	v3.tangent += tangent;
}

bool ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	shaders.push_back(make_shared<ColorShader>());
	shaders.push_back(make_shared<ColorInstancedShader>());
	shaders.push_back(make_shared<GlobalDiffuseShader>());
	shaders.push_back(make_shared<GlobalSpecularShader>());
	shaders.push_back(make_shared<PointDiffuseShader>());
	shaders.push_back(make_shared<PointSpecularShader>());
	shaders.push_back(make_shared<TextureShader>());
	shaders.push_back(make_shared<NormalMappedShader>());
	for(auto &shader : shaders)
		shader->Init(device);
	return true;
}