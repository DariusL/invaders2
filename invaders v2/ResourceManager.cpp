#include "includes.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
using namespace e;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(ID3D11Device *device)
:letters(GetModelsFromOBJ(L"Resources\\text.obj"))
{
	handle = this;

	VertexType vt;
	Geometry<VertexType> plane;

	vt.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	plane.Add(vt);

	vt.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	plane.Add(vt);

	vt.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	plane.Add(vt);

	vt.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	plane.Add(vt);

	plane.indices.push_back(1);
	plane.indices.push_back(2);
	plane.indices.push_back(0);

	plane.indices.push_back(1);
	plane.indices.push_back(3);
	plane.indices.push_back(2);

	models.emplace_back(device, plane);
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\player.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy1.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy2.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy3.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy4.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy5.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\enemy6.obj"));
	models.emplace_back(device, GetModelFromOBJ(L"Resources\\bullet.obj"));

	Level *level = new Level();

	level->gridWidth = 11;
	level->gridHeight = 5;

	for (int i = 0; i < level->gridHeight * level->gridWidth; i++)
	{
		level->enemies.push_back(MODEL::MODEL_PLAYER);
	}

	levels.push_back(shared_ptr<Level>(level));

	shaders.push_back(make_unique<ColorShader>(L"Shaders\\ColorVertex.cso", L"Shaders\\ColorPixel.cso"));
	shaders.push_back(make_unique<ColorInstancedShader>(L"Shaders\\ColorInstancedVertex.cso", L"Shaders\\ColorInstancedPixel.cso"));
	shaders.push_back(make_unique<GlobalDiffuseShader>(L"Shaders\\GlobalDiffuseVertex.cso", L"Shaders\\GlobalDiffusePixel.cso"));
	shaders.push_back(make_unique<GlobalSpecularShader>(L"Shaders\\GlobalSpecularVertex.cso", L"Shaders\\GlobalSpecularPixel.cso"));
	shaders.push_back(make_unique<TextureShader>(L"Shaders\\TextureVertex.cso", L"Shaders\\TexturePixel.cso"));

	computeShaders.push_back(make_unique<CelComputeShader>(L"Shaders\\CelCompute.cso"));
	computeShaders.push_back(make_unique<UpSampleComputeShader>(L"Shaders\\UpSampleCompute.cso"));
	computeShaders.push_back(make_unique<DownSampleComputeShader>(L"Shaders\\DownSampleCompute.cso"));
	computeShaders.push_back(make_unique<HorizontalBlurComputeShader>(L"Shaders\\BlurCompute.cso"));
	computeShaders.push_back(make_unique<VerticalBlurComputeShader>(L"Shaders\\BlurCompute.cso"));
	computeShaders.push_back(make_unique<FilterDownSampleShader>(L"Shaders\\FilterDownSampleCompute.cso"));
	computeShaders.push_back(make_unique<TexelSumComputeShader>(L"Shaders\\TexelSumCompute.cso"));
	computeShaders.push_back(make_unique<CopyComputeShader>(L"Shaders\\CopyCompute.cso"));

	for (auto &shader : shaders)
		shader->Init(device);

	for (auto &shader : computeShaders)
		shader->Init(device);
}

Geometry<VertexType> ResourceManager::GetModelFromOBJ(wstring filename, bool invert)
{
	ifstream in(filename, ios::binary);
	Geometry<VertexType> g;
	string input;
	float x, y, z;

	AssertBool(in.is_open(), L"File " + filename + L" not found");

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
			g.Add(x, y, -z);
		}
		else if (input == "f")
		{
			string blob;
			getline(in, blob, '\n');
			auto fvert = GetVerticesFromFace(blob);
			if (!invert)
			{
				Utils::Reverse(fvert);
			}
			for (auto &vertex : fvert)
			{
				g.indices.push_back(vertex.vertex);
			}
		}
	}

	return g;
}

unordered_map<char, Geometry<VertexType>> ResourceManager::GetModelsFromOBJ(wstring filename)
{
	unordered_map<char, Geometry<VertexType>> ret;
	ifstream in(filename, ios::binary);
	Geometry<VertexType> g;
	string input;
	float x, y, z;
	int voff = 1;
	string name;
	bool object = false;

	AssertBool(in.is_open(), L"File " + filename + L" not found");

	while (!in.eof())
	{
		in >> input;

		if (object)
		{
			if (input == "f")
			{
				string blob;
				getline(in, blob, '\n');
				auto fvert = GetVerticesFromFace(blob, voff);
				Utils::Reverse(fvert);
				for (auto &vertex : fvert)
				{
					g.indices.push_back(vertex.vertex);
				}
			}
			else
			{
				if (name == "_")
					name.length();
				object = false;
				voff += g.vertices.size();
				g.Center();
				ret.emplace(name[0], move(g));
				in.ignore(200, '\n');
			}
		}
		else
		{
			if (input == "#" || input == "vt" || input == "vn")
			{
				in.ignore(200, '\n');
			}
			else if (input == "v")
			{
				in >> x >> y >> z;
				g.Add(x, y, -z);
			}
			else if (input == "g")
			{
				in >> name;
				object = true;
			}
		}
	}
	return ret;
}

Geometry<NormalVertexType> ResourceManager::GetNormalModelFromOBJ(wstring filename, bool invert)
{
	Geometry<NormalVertexType> g;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT3> normals;
	string input;
	float x, y, z;

	AssertBool(in.is_open(), L"File " + filename + L" not found");

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
			g.Add(x, y, -z);
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
			auto fvert = GetVerticesFromFace(blob);
			if (!invert)
			{
				Utils::Reverse(fvert);
			}
			for (auto &vertex : fvert)
			{
				g.vertices[vertex.vertex].normal = normals[vertex.normal];
				g.indices.push_back(vertex.vertex);
			}
		}
	}

	return g;
}

vector<ResourceManager::FaceVertex> ResourceManager::GetVerticesFromFace(string &line, int voff, int noff, int toff)
{
	vector<FaceVertex> ret;
	int ind1 = 0, ind2 = 0;

	for (int i = 0; i < 3; i++)
	{
		ind2 = line.find(' ', ind1 + 1);
		ret.push_back(GetVertexFromString(line.substr(ind1, ind2 - ind1), voff, noff, toff));
		ind1 = ++ind2;
	}
	return ret;
}

ResourceManager::FaceVertex ResourceManager::GetVertexFromString(string &vertex, int voff, int noff, int toff)
{
	FaceVertex ret;
	string temp;
	int ind1 = 0, ind2 = 0;

	ind1 = vertex.find('/');
	temp = vertex.substr(0, ind1);
	ret.vertex = temp.length() > 0 ? stoi(temp) - voff : -1;
	ind2 = vertex.find('/', ind1 + 1);
	temp = vertex.substr(ind1 + 1, ind2 - ind1 - 1);
	ret.tex = temp.length() > 0 ? stoi(temp) - toff : -1;
	temp = vertex.substr(ind2 + 1);
	ret.normal = temp.length() > 0 ? stoi(temp) - noff : -1;

	return ret;
}

ComPtr<ID3D11ShaderResourceView> ResourceManager::GetTextureFromFile(wstring filename, ID3D11Device *device)
{
	ComPtr<ID3D11ShaderResourceView> ret;
	Assert(CreateDDSTextureFromFile(device, filename.c_str(), NULL, &ret));
	return ret;
}