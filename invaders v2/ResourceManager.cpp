#include "includes.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
using namespace Microsoft::WRL;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(void)
:normalMappedModel(GetNormalMappedModelFromOBJ("textured_ball.obj")),
	normalModel(GetNormalModelFromOBJ("teapot.obj")),
	models()
{
	normalMappedModel.hitbox = XMFLOAT2(2.0f, 2.0f);
	normalModel.hitbox = XMFLOAT2(1.5f, 1.5f);
	handle = this;
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

void ResourceManager::Init()
{
	//player
	ColorModel temp;
	temp.hitbox = XMFLOAT2(2.0f, 2.0f);

	VertexType vertex;
	
	vertex.position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	models.push_back(move(temp));

	//enemy basic
	temp.hitbox = XMFLOAT2(2.0f, 2.0f);
	
	vertex.position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	models.push_back(move(temp));

	//bullet
	temp.hitbox = XMFLOAT2(0.2f, 1.5f);
	
	vertex.position = XMFLOAT3(-0.1f, -0.75f, 0.0f);  // Bottom left.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(-0.1f, 0.75f, 0.0f);  // Top left
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(0.1f, -0.75f, 0.0f);  // Bottom right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(0.1f, 0.75f, 0.0f);  // Top right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	temp.vertices.push_back(vertex);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	models.push_back(move(temp));

	//enemy laptop
	temp.hitbox = XMFLOAT2(2.0f, 2.0f);

	vertex.position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left
	vertex.color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top right.
	vertex.color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	models.push_back(move(temp));

	//wall
	temp.hitbox = XMFLOAT2(1.0f, 1.0f);
	
	vertex.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	vertex.color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	vertex.color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	vertex.color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	vertex.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	vertex.color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	temp.vertices.push_back(vertex);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	models.push_back(move(temp));

	temp = GetModelFromOBJ("ball.obj");
	temp.hitbox = XMFLOAT2(2.0f, 2.0f);

	models.push_back(move(temp));

	TexturedModel plane;
	plane.hitbox = XMFLOAT2(20, 20);

	TextureVertexType tv;

	tv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	tv.tex = XMFLOAT2(0.0f, 1.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	tv.tex = XMFLOAT2(0.0f, 0.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	tv.tex = XMFLOAT2(1.0f, 1.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	tv.tex = XMFLOAT2(1.0f, 0.0f);
	plane.vertices.push_back(tv);

	plane.indices.push_back(1);
	plane.indices.push_back(2);
	plane.indices.push_back(0);

	plane.indices.push_back(1);
	plane.indices.push_back(3);
	plane.indices.push_back(2);

	texturedModels.push_back(move(plane));
	texturedModels.push_back(GetTexturedModelFromOBJUnindexed("box.obj"));

	Level *level = new Level();

	level->gridWidth = 11;
	level->gridHeight = 5;
	level->gap = XMFLOAT2(3.0f, 3.0f);
	level->enemyTypes = vector<int>();
	level->enemyTypes.push_back(Enemies::BASIC);

	for(int i = 0; i < level->gridHeight * level->gridWidth; i++)
	{
		level->enemies.push_back(Enemies::BASIC);
	}

	levels.push_back(shared_ptr<Level>(level));
}

ColorModel ResourceManager::GetModelFromOBJ(string filename, bool invert)
{
	auto normalModel = GetNormalModelFromOBJ(filename, invert);
	ColorModel ret;
	VertexType vertex;
	ret.hitbox = normalModel.hitbox;
	ret.indices = normalModel.indices;
	for(NormalVertexType normalVertex : normalModel.vertices)
	{
		vertex.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex.position = normalVertex.position;
		ret.vertices.push_back(vertex);
	}
	return ret;
}

NormalModel ResourceManager::GetNormalModelFromOBJ(string filename, bool invert)
{
	NormalModel model;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT3> normals;
	string input;
	float x, y, z;

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
			model.vertices.emplace_back(x, y, -z);
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
			if (!invert)
			{
				Utils::Reverse(vertices);
			}
			for(auto &vertex : vertices)
			{
				model.vertices[vertex.vertex].normal = normals[vertex.normal];
				model.indices.push_back(vertex.vertex);
			}
		}
	}

	return model;
}

NormalMappedModel ResourceManager::GetNormalMappedModelFromOBJ(string filename, bool invert)
{
	NormalMappedModel model;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT3> normals;
	vector<XMFLOAT2> tex;
	string input;
	float x, y, z;

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
			model.vertices.emplace_back(x, y, -z);
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
			if (!invert)
			{
				Utils::Reverse(vertices);
			}
			for(auto &vertex : vertices)
			{
				model.vertices[vertex.vertex].normal = normals[vertex.normal];
				model.vertices[vertex.vertex].tex = tex[vertex.tex];
				model.indices.push_back(vertex.vertex);
			}
			CalculateTangentAndBinormal(vertices, model.vertices);
		}
	}

	return model;
}

TexturedModel ResourceManager::GetTexturedModelFromOBJ(string filename, bool invert)
{
	TexturedModel model;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT2> tex;
	string input;
	float x, y, z;

	while (!in.eof())
	{
		in >> input;

		if (input == "#")
		{
			in.ignore(200, '\n');
			continue;
		}

		if (input == "v")
		{
			in >> x >> y >> z;
			model.vertices.emplace_back(x, y, -z);
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
			if (!invert)
			{
				Utils::Reverse(vertices);
			}
			for (auto &vertex : vertices)
			{
				model.vertices[vertex.vertex].tex = tex[vertex.tex];
				model.indices.push_back(vertex.vertex);
			}
		}
	}

	return model;
}

TexturedModel ResourceManager::GetTexturedModelFromOBJUnindexed(string filename, bool invert)
{
	TexturedModel model;
	vector<TextureVertexType> v;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT2> tex;
	string input;
	float x, y, z;

	while (!in.eof())
	{
		in >> input;

		if (input == "#")
		{
			in.ignore(200, '\n');
			continue;
		}

		if (input == "v")
		{
			in >> x >> y >> z;
			v.emplace_back(x, y, -z);
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
			if (!invert)
			{
				Utils::Reverse(vertices);
			}
			for (auto &vertex : vertices)
			{
				TextureVertexType temp = v[vertex.vertex];
				temp.tex = tex[vertex.tex];
				model.vertices.push_back(temp);
				model.indices.push_back(model.vertices.size() - 1);
			}
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

	XMFLOAT2 tu(v2.tex.x - v1.tex.x, v3.tex.x - v1.tex.x);
	XMFLOAT2 tv(v2.tex.y - v1.tex.y, v3.tex.y - v1.tex.y);

	XMVECTOR edge1 = XMLoadFloat3(&v2.position) - XMLoadFloat3(&v1.position);
	XMVECTOR edge2 = XMLoadFloat3(&v3.position) - XMLoadFloat3(&v1.position);

	float den = 1.0f / (tu.x * tv.y - tu.y * tv.x);

	XMVECTOR tangent = XMVector3Normalize((tv.y * edge1 - tv.x * edge2) * den);
	XMVECTOR binormal = XMVector3Normalize((tu.x * edge2 - tv.y * edge1) * den);

	XMStoreFloat3(&v1.binormal, binormal + XMLoadFloat3(&v1.binormal));
	XMStoreFloat3(&v1.tangent, tangent + XMLoadFloat3(&v1.tangent));

	XMStoreFloat3(&v2.binormal, binormal + XMLoadFloat3(&v2.binormal));
	XMStoreFloat3(&v2.tangent, tangent + XMLoadFloat3(&v2.binormal));

	XMStoreFloat3(&v3.binormal, binormal + XMLoadFloat3(&v3.binormal));
	XMStoreFloat3(&v3.tangent, tangent + XMLoadFloat3(&v3.tangent));
}

ComPtr<ID3D11ShaderResourceView> ResourceManager::GetTextureFromFile(wstring filename, ComPtr<ID3D11Device> device)
{
	ComPtr<ID3D11ShaderResourceView> ret;
	Assert(CreateDDSTextureFromFile(device.Get(), filename.c_str(), NULL, ret.GetAddressOf()));
	//Assert(D3DX11CreateShaderResourceViewFromFile(device.Get(), filename.c_str(), NULL, NULL, &ret, NULL));
	return ret;
}

void ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	shaders.push_back(make_unique<ColorShader>(L"ColorVertex.cso", L"ColorPixel.cso"));
	shaders.push_back(make_unique<ColorInstancedShader>(L"ColorInstancedVertex.cso", L"ColorPixel.cso"));
	shaders.push_back(make_unique<GlobalDiffuseShader>(L"GlobalDiffuseVertex.cso", L"GlobalDiffusePixel.cso"));
	shaders.push_back(make_unique<GlobalSpecularShader>(L"GlobalSpecularVertex.cso", L"GlobalSpecularPixel.cso"));
	shaders.push_back(make_unique<PointDiffuseShader>(L"PointDiffuseVertex.cso", L"PointDiffusePixel.cso"));
	shaders.push_back(make_unique<PointSpecularShader>(L"PointSpecularVertex.cso", L"PointSpecularPixel.cso"));
	shaders.push_back(make_unique<TextureShader>(L"TextureVertex.cso", L"TexturePixel.cso"));
	shaders.push_back(make_unique<NormalMappedShader>(L"NormalMapVertex.cso", L"NormalMapPixel.cso"));
	shaders.push_back(make_unique<WaterShader>(L"WaterVertex.cso", L"WaterPixel.cso"));
	shaders.push_back(make_unique<MirrorShader>(L"MirrorVertex.cso", L"MirrorPixel.cso"));
	
	for(auto &shader : shaders)
		shader->Init(device);

	textures.push_back(GetTextureFromFile(L"gaben.dds", device));
	textures.push_back(GetTextureFromFile(L"stage7.dds", device));
	textures.push_back(GetTextureFromFile(L"wave.dds", device));
	textures.push_back(GetTextureFromFile(L"freaky_rectangles.dds", device));
}