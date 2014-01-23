#include "includes.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
using namespace Microsoft::WRL;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device)
:normalMappedModel(device, GetNormalMappedModelFromOBJ(L"Resources\\ball.obj"))
{
	handle = this;

	models.emplace_back(device, GetModelFromOBJ(L"Resources\\ball.obj"));

	TextureVertexType tv;
	Geometry<TextureVertexType> temp;

	tv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	tv.tex = XMFLOAT2(0.0f, 1.0f);
	temp.vertices.push_back(tv);

	tv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	tv.tex = XMFLOAT2(0.0f, 0.0f);
	temp.vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	tv.tex = XMFLOAT2(1.0f, 1.0f);
	temp.vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	tv.tex = XMFLOAT2(1.0f, 0.0f);
	temp.vertices.push_back(tv);

	temp.indices.push_back(1);
	temp.indices.push_back(2);
	temp.indices.push_back(0);

	temp.indices.push_back(1);
	temp.indices.push_back(3);
	temp.indices.push_back(2);

	texturedModels.push_back(TexturedModel(device, temp));
	temp.vertices.clear();

	texturedModels.emplace_back(device, GetTexturedModelFromOBJ(L"Resources\\box.obj", true));
	texturedModels.emplace_back(device, GetTexturedModelFromOBJ(L"Resources\\bath.obj", true));

	normalTexturedModels.emplace_back(device, GetNormalTexturedModelFromOBJ(L"Resources\\box.obj", true));
	Geometry<NormalTextureVertexType> vert;
	NormalTextureVertexType ntv;
	ntv.normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	ntv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	ntv.tex = XMFLOAT2(0.0f, 1.0f);
	vert.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	ntv.tex = XMFLOAT2(0.0f, 0.0f);
	vert.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	ntv.tex = XMFLOAT2(1.0f, 1.0f);
	vert.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	ntv.tex = XMFLOAT2(1.0f, 0.0f);
	vert.vertices.push_back(ntv);

	vert.indices.push_back(1);
	vert.indices.push_back(2);
	vert.indices.push_back(0);

	vert.indices.push_back(1);
	vert.indices.push_back(3);
	vert.indices.push_back(2);

	normalTexturedModels.emplace_back(device, vert);
	vert.vertices.clear();
	normalTexturedModels.emplace_back(device, GetNormalTexturedModelFromOBJ(L"Resources\\bath.obj", true));

	Level *level = new Level();

	level->gridWidth = 11;
	level->gridHeight = 5;
	level->gap = XMFLOAT2(3.0f, 3.0f);
	level->enemyTypes = vector<int>();
	level->enemyTypes.push_back(ENEMY::ENEMY_BASIC);

	for (int i = 0; i < level->gridHeight * level->gridWidth; i++)
	{
		level->enemies.push_back(ENEMY::ENEMY_BASIC);
	}

	levels.push_back(shared_ptr<Level>(level));

	shaders.push_back(make_unique<ColorShader>(L"Shaders\\ColorVertex.cso", L"Shaders\\ColorPixel.cso"));
	shaders.push_back(make_unique<ColorInstancedShader>(L"Shaders\\ColorInstancedVertex.cso", L"Shaders\\ColorPixel.cso"));
	shaders.push_back(make_unique<GlobalDiffuseShader>(L"Shaders\\GlobalDiffuseVertex.cso", L"Shaders\\GlobalDiffusePixel.cso"));
	shaders.push_back(make_unique<GlobalSpecularShader>(L"Shaders\\GlobalSpecularVertex.cso", L"Shaders\\GlobalSpecularPixel.cso"));
	shaders.push_back(make_unique<TextureShader>(L"Shaders\\TextureVertex.cso", L"Shaders\\TexturePixel.cso"));
	shaders.push_back(make_unique<InstancedTextureShader>(L"Shaders\\TextureInstancedVertex.cso", L"Shaders\\TexturePixel.cso"));

	computeShaders.push_back(make_unique<CelComputeShader>(L"Shaders\\CelCompute.cso"));
	computeShaders.push_back(make_unique<UpSampleComputeShader>(L"Shaders\\UpSampleCompute.cso"));
	computeShaders.push_back(make_unique<DownSampleComputeShader>(L"Shaders\\DownSampleCompute.cso"));
	computeShaders.push_back(make_unique<HorizontalBlurComputeShader>(L"Shaders\\BlurCompute.cso"));
	computeShaders.push_back(make_unique<VerticalBlurComputeShader>(L"Shaders\\BlurCompute.cso"));
	computeShaders.push_back(make_unique<FilterDownSampleShader>(L"Shaders\\FilterDownSampleCompute.cso"));
	computeShaders.push_back(make_unique<TexelSumComputeShader>(L"Shaders\\TexelSumCompute.cso"));

	for (auto &shader : shaders)
		shader->Init(device);

	for (auto &shader : computeShaders)
		shader->Init(device);

	textures.push_back(GetTextureFromFile(L"Resources\\gaben.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\wave.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\concrete.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\tree.dds", device));
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
			g.vertices.emplace_back(x, y, -z);
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
			g.vertices.emplace_back(x, y, -z);
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

Geometry<NormalMappedVertexType> ResourceManager::GetNormalMappedModelFromOBJ(wstring filename, bool invert)
{
	Geometry<NormalMappedVertexType> g;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT3> normals;
	vector<XMFLOAT2> tex;
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
			g.vertices.emplace_back(x, y, -z);
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
			auto fvert = GetVerticesFromFace(blob);
			if (!invert)
			{
				Utils::Reverse(fvert);
			}
			for (auto &vertex : fvert)
			{
				g.vertices[vertex.vertex].normal = normals[vertex.normal];
				g.vertices[vertex.vertex].tex = tex[vertex.tex];
				g.indices.push_back(vertex.vertex);
			}
			CalculateTangentAndBinormal(fvert, g.vertices);
		}
	}

	return g;
}

Geometry<TextureVertexType> ResourceManager::GetTexturedModelFromOBJ(wstring filename, bool unindex, bool invert)
{
	Geometry<TextureVertexType> g;
	vector<TextureVertexType> temp;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT2> tex;
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
			if (unindex)
				temp.emplace_back(x, y, -z);
			else
				g.vertices.emplace_back(x, y, -z);
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
			auto fvert = GetVerticesFromFace(blob);
			if (!invert)
			{
				Utils::Reverse(fvert);
			}
			if (unindex)
			{
				for (auto &vertex : fvert)
				{
					TextureVertexType vt = temp[vertex.vertex];
					vt.tex = tex[vertex.tex];
					g.vertices.push_back(vt);
					g.indices.push_back(g.vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : fvert)
				{
					g.vertices[vertex.vertex].tex = tex[vertex.tex];
					g.indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return g;
}

Geometry<NormalTextureVertexType> ResourceManager::GetNormalTexturedModelFromOBJ(wstring filename, bool unindex, bool invert)
{
	Geometry<NormalTextureVertexType> g;
	vector<NormalTextureVertexType> temp;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT2> tex;
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
			if (unindex)
				temp.emplace_back(x, y, -z);
			else
				g.vertices.emplace_back(x, y, -z);
		}
		else if (input == "vt")
		{
			in >> x >> y >> z;
			tex.emplace_back(x, y);
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
			if (unindex)
			{
				for (auto &vertex : fvert)
				{
					NormalTextureVertexType vt = temp[vertex.vertex];
					vt.tex = tex[vertex.tex];
					vt.normal = normals[vertex.normal];
					g.vertices.push_back(vt);
					g.indices.push_back(g.vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : fvert)
				{
					g.vertices[vertex.vertex].tex = tex[vertex.tex];
					g.vertices[vertex.vertex].normal = normals[vertex.normal];
					g.indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return g;
}

vector<ResourceManager::FaceVertex> ResourceManager::GetVerticesFromFace(string &line)
{
	vector<FaceVertex> ret;
	int ind1 = 0, ind2 = 0;

	for (int i = 0; i < 3; i++)
	{
		ind2 = line.find(' ', ind1 + 1);
		ret.push_back(GetVertexFromString(line.substr(ind1, ind2 - ind1)));
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
	ind2 = vertex.find('/', ind1 + 1);
	temp = vertex.substr(ind1 + 1, ind2 - ind1 - 1);
	ret.tex = temp.length() > 0 ? stoi(temp) - 1 : -1;
	temp = vertex.substr(ind2 + 1);
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
	Assert(CreateDDSTextureFromFile(device.Get(), filename.c_str(), NULL, &ret));
	return ret;
}