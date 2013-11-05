#include "includes.h"
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
		return make_shared<DrawableShooter>(15.0f, 0.5f, models[Models::MODEL_ENEMY_BASIC], GetShader<ColorShader>());
		break;
	case Enemies::LAPTOP:
		return make_shared<DrawableShooter>(15.0f, 0.5f, models[Models::MODEL_ENEMY_LAPTOP], GetShader<ColorShader>());
	default:
		return NULL;
		break;
	}
}

bool ResourceManager::Init()
{
	//player
	shared_ptr<Model<VertexType>> temp = make_shared<Model<VertexType>>();
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
	temp = make_shared<Model<VertexType>>();
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
	temp = make_shared<Model<VertexType>>();
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
	temp = make_shared<Model<VertexType>>();
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
	temp = make_shared<ColorModel>();
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

	plane = make_shared<TexturedModel>();
	plane->hitbox = D3DXVECTOR2(20, 20);
	TextureVertexType tv;

	tv.position = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);  // Bottom left.
	tv.tex = D3DXVECTOR2(0.0f, 1.0f);
	plane->vertices.push_back(tv);

	tv.position = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);  // Top left
	tv.tex = D3DXVECTOR2(0.0f, 0.0f);
	plane->vertices.push_back(tv);

	tv.position = D3DXVECTOR3(10.0f, -10.0f, 0.0f);  // Bottom right.
	tv.tex = D3DXVECTOR2(1.0f, 1.0f);
	plane->vertices.push_back(tv);

	tv.position = D3DXVECTOR3(10.0f, 10.0f, 0.0f);  // Top right.
	tv.tex = D3DXVECTOR2(1.0f, 0.0f);
	plane->vertices.push_back(tv);

	plane->indices.push_back(1);
	plane->indices.push_back(2);
	plane->indices.push_back(0);

	plane->indices.push_back(1);
	plane->indices.push_back(3);
	plane->indices.push_back(2);

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

unique_ptr<ColorModel> ResourceManager::GetModelFromOBJ(char *filename)
{
	auto normalModel = GetNormalModelFromOBJ(filename);
	auto ret = unique_ptr<Model<VertexType>>(new Model<VertexType>());
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
	auto model = unique_ptr<Model<NormalVertexType>>(new Model<NormalVertexType>());
	ifstream in(filename, ios::binary);
	vector<D3DXVECTOR3> normals;
	string input;
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
			model->vertices.emplace_back(x, y, -z);
		}
		else if (input == "vn")
		{
			in >> x >> y >> z;
			normals.emplace_back(x, y, -z);
		}
		else if (input == "f")
		{
			string blob;
			getline(in, blob, '\n');
			auto vertices = GetVerticesFromFace(blob);
			Utils::Reverse(vertices);
			for(auto &vertex : vertices)
			{
				model->vertices[vertex.vertex].normal = normals[vertex.normal];
				model->indices.push_back(vertex.vertex);
			}
		}
	}

	return model;
}

unique_ptr<NormalMappedModel> ResourceManager::GetTexturedModelFromOBJ(char *filename)
{
	auto model = unique_ptr<Model<NormalMappedVertexType>>(new Model<NormalMappedVertexType>());
	ifstream in(filename, ios::binary);
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> tex;
	string input;
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
			model->vertices.emplace_back(x, y, -z);
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
			getline(in, blob, '\n');
			auto vertices = GetVerticesFromFace(blob);
			Utils::Reverse(vertices);
			for(auto &vertex : vertices)
			{
				model->vertices[vertex.vertex].normal = normals[vertex.normal];
				model->vertices[vertex.vertex].tex = tex[vertex.tex];
				model->indices.push_back(vertex.vertex);
			}
			CalculateTangentAndBinormal(vertices, model->vertices);
		}
	}

	return model;
}

vector<ResourceManager::FaceVertex> ResourceManager::GetVerticesFromFace(string &line)
{
	vector<FaceVertex> ret;
	int ind1 = 0, ind2 = 0;

	for(int i = 0; i < 3; i++)
	{
		ind2 = line.find(' ', ind1+1);
		ret.push_back(GetVertexFromString(line.substr(ind1, ind2-ind1)));
		ind1 = ++ind2;
	}
	return ret;
}

ResourceManager::FaceVertex ResourceManager::GetVertexFromString(string &vertex)
{
	FaceVertex ret;
	string temp;
	int ind1 = 0, ind2 = 0;

	ind1 = vertex.find('/');
	temp = vertex.substr(0, ind1);
	ret.vertex = temp.length() > 0 ? stoi(temp) - 1 : -1;
	ind2 = vertex.find('/', ind1+1);
	temp = vertex.substr(ind1+1, ind2-ind1-1);
	ret.tex = temp.length() > 0 ? stoi(temp) - 1 : -1;
	temp = vertex.substr(ind2+1);
	ret.normal = temp.length() > 0 ? stoi(temp) - 1 : -1;

	return ret;
}

void ResourceManager::CalculateTangentAndBinormal(const vector<FaceVertex> &ind, vector<NormalMappedVertexType> &v)
{
	auto &v1 = v[ind[0].vertex];
	auto &v2 = v[ind[1].vertex];
	auto &v3 = v[ind[2].vertex];

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
	shaders.push_back(unique_ptr<ColorShader>(new ColorShader("ColorVertex.cso", "ColorPixel.cso")));
	shaders.push_back(unique_ptr<ColorInstancedShader>(new ColorInstancedShader("ColorInstancedVertex.cso", "ColorPixel.cso")));
	shaders.push_back(unique_ptr<GlobalDiffuseShader>(new GlobalDiffuseShader("GlobalDiffuseVertex.cso", "GlobalDiffusePixel.cso")));
	shaders.push_back(unique_ptr<GlobalSpecularShader>(new GlobalSpecularShader("GlobalSpecularVertex.cso", "GlobalSpecularPixel.cso")));
	shaders.push_back(unique_ptr<PointDiffuseShader>(new PointDiffuseShader("PointDiffuseVertex.cso", "PointDiffusePixel.cso")));
	shaders.push_back(unique_ptr<PointSpecularShader>(new PointSpecularShader("PointSpecularVertex.cso", "PointSpecularPixel.cso")));
	shaders.push_back(unique_ptr<TextureShader>(new TextureShader("TextureVertex.cso", "TexturePixel.cso")));
	shaders.push_back(unique_ptr<NormalMappedShader>(new NormalMappedShader("NormalMapVertex.cso", "NormalMapPixel.cso")));
	shaders.push_back(unique_ptr<WaterShader>(new WaterShader("WaterVertex.cso", "WaterPixel.cso")));
	for(auto &shader : shaders)
		shader->Init(device);
	return true;
}