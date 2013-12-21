#include "includes.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
using namespace Microsoft::WRL;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device)
:normalMappedModel(GetNormalMappedModelFromOBJ(device, L"Resources\\ball.obj"))
{
	handle = this;

	models.push_back(GetModelFromOBJ(device, L"Resources\\ball.obj"));

	TextureVertexType tv;
	vector<TextureVertexType> vertices;
	vector<int> indices;

	tv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	tv.tex = XMFLOAT2(0.0f, 1.0f);
	vertices.push_back(tv);

	tv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	tv.tex = XMFLOAT2(0.0f, 0.0f);
	vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	tv.tex = XMFLOAT2(1.0f, 1.0f);
	vertices.push_back(tv);

	tv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	tv.tex = XMFLOAT2(1.0f, 0.0f);
	vertices.push_back(tv);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	texturedModels.push_back(TexturedModel(device, vertices, indices));
	vertices.clear();

	texturedModels.push_back(GetTexturedModelFromOBJ(device, L"Resources\\box.obj", true));
	texturedModels.push_back(GetTexturedModelFromOBJ(device, L"Resources\\bath.obj", true));

	normalTexturedModels.push_back(GetNormalTexturedModelFromOBJ(device, L"Resources\\box.obj", true));
	vector<NormalTextureVertexType> vert;
	NormalTextureVertexType ntv;
	ntv.normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	ntv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	ntv.tex = XMFLOAT2(0.0f, 1.0f);
	vert.push_back(ntv);

	ntv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	ntv.tex = XMFLOAT2(0.0f, 0.0f);
	vert.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	ntv.tex = XMFLOAT2(1.0f, 1.0f);
	vert.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	ntv.tex = XMFLOAT2(1.0f, 0.0f);
	vert.push_back(ntv);

	normalTexturedModels.push_back(NormalTexturedModel(device, vert, indices));
	vert.clear();
	normalTexturedModels.push_back(GetNormalTexturedModelFromOBJ(device, L"Resources\\bath.obj", true));

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
	shaders.push_back(make_unique<PointDiffuseShader>(L"Shaders\\PointDiffuseVertex.cso", L"Shaders\\PointDiffusePixel.cso"));
	shaders.push_back(make_unique<PointSpecularShader>(L"Shaders\\PointSpecularVertex.cso", L"Shaders\\PointSpecularPixel.cso"));
	shaders.push_back(make_unique<TextureShader>(L"Shaders\\TextureVertex.cso", L"Shaders\\TexturePixel.cso"));
	shaders.push_back(make_unique<NormalMappedShader>(L"Shaders\\NormalMapVertex.cso", L"Shaders\\NormalMapPixel.cso"));
	shaders.push_back(make_unique<WaterShader>(L"Shaders\\WaterVertex.cso", L"Shaders\\WaterPixel.cso"));
	shaders.push_back(make_unique<MirrorShader>(L"Shaders\\MirrorVertex.cso", L"Shaders\\MirrorPixel.cso"));
	shaders.push_back(make_unique<InstancedTextureShader>(L"Shaders\\TextureInstancedVertex.cso", L"Shaders\\TexturePixel.cso"));
	shaders.push_back(make_unique<ShadowShader>(L"Shaders\\ShadowVertex.cso", L"Shaders\\ShadowPixel.cso"));
	shaders.push_back(make_unique<HorizontalBlurShader>(L"Shaders\\TextureVertex.cso", L"Shaders\\HorizontalBlurPixel.cso"));
	shaders.push_back(make_unique<VerticalBlurShader>(L"Shaders\\TextureVertex.cso", L"Shaders\\VerticalBlurPixel.cso"));

	computeShaders.push_back(make_unique<CelComputeShader>(L"Shaders\\CelCompute.cso"));
	computeShaders.push_back(make_unique<UpSampleComputeShader>(L"Shaders\\UpSampleCompute.cso"));
	computeShaders.push_back(make_unique<DownSampleComputeShader>(L"Shaders\\DownSampleCompute.cso"));

	for (auto &shader : shaders)
		shader->Init(device);

	for (auto &shader : computeShaders)
		shader->Init(device);

	textures.push_back(GetTextureFromFile(L"Resources\\gaben.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\wave.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\concrete.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\tree.dds", device));
}

ColorModel ResourceManager::GetModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert)
{
	ifstream in(filename, ios::binary);
	vector<VertexType> vertices;
	vector<int> indices;
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
			vertices.emplace_back(x, y, -z);
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
				indices.push_back(vertex.vertex);
			}
		}
	}

	return ColorModel(device, vertices, indices);
}

NormalModel ResourceManager::GetNormalModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert)
{
	vector<NormalVertexType> vertices;
	vector<int> indices;
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
			vertices.emplace_back(x, y, -z);
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
				vertices[vertex.vertex].normal = normals[vertex.normal];
				indices.push_back(vertex.vertex);
			}
		}
	}

	return NormalModel(device, vertices, indices);
}

NormalMappedModel ResourceManager::GetNormalMappedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool invert)
{
	vector<NormalMappedVertexType> vertices;
	vector<int> indices;
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
			vertices.emplace_back(x, y, -z);
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
				vertices[vertex.vertex].normal = normals[vertex.normal];
				vertices[vertex.vertex].tex = tex[vertex.tex];
				indices.push_back(vertex.vertex);
			}
			CalculateTangentAndBinormal(fvert, vertices);
		}
	}

	return NormalMappedModel(device, vertices, indices);
}

TexturedModel ResourceManager::GetTexturedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool unindex, bool invert)
{
	vector<TextureVertexType> vertices, temp;
	vector<int> indices;
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
				vertices.emplace_back(x, y, -z);
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
					vertices.push_back(vt);
					indices.push_back(vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : fvert)
				{
					vertices[vertex.vertex].tex = tex[vertex.tex];
					indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return TexturedModel(device, vertices, indices);
}

NormalTexturedModel ResourceManager::GetNormalTexturedModelFromOBJ(ComPtr<ID3D11Device> device, wstring filename, bool unindex, bool invert)
{
	vector<NormalTextureVertexType> temp , vertices;
	vector<int> indices;
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
				vertices.emplace_back(x, y, -z);
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
					vertices.push_back(vt);
					indices.push_back(vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : fvert)
				{
					vertices[vertex.vertex].tex = tex[vertex.tex];
					vertices[vertex.vertex].normal = normals[vertex.normal];
					indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return NormalTexturedModel(device, vertices, indices);
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