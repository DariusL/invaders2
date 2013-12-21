#include "includes.h"
#include "ResourceManager.h"
#include "DDSTextureLoader.h"
using namespace Microsoft::WRL;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device)
:normalMappedModel(GetNormalMappedModelFromOBJ(L"Resources\\ball.obj"))
{
	handle = this;

	models.push_back(GetModelFromOBJ(L"Resources\\ball.obj"));

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

	texturedModels.push_back(GetTexturedModelFromOBJ(L"Resources\\box.obj", true));
	texturedModels.push_back(GetTexturedModelFromOBJ(L"Resources\\bath.obj", true));

	tv.position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Bottom left.
	tv.tex = XMFLOAT2(0.0f, 1.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(0.0f, 0.0f, 0.0f);  // Top left
	tv.tex = XMFLOAT2(0.0f, 0.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Bottom right.
	tv.tex = XMFLOAT2(1.0f, 1.0f);
	plane.vertices.push_back(tv);

	tv.position = XMFLOAT3(1.0f, 0.0f, 0.0f);  // Top right.
	tv.tex = XMFLOAT2(1.0f, 0.0f);
	plane.vertices.push_back(tv);

	plane.indices.push_back(1);
	plane.indices.push_back(2);
	plane.indices.push_back(0);

	plane.indices.push_back(1);
	plane.indices.push_back(3);
	plane.indices.push_back(2);
	texturedModels.push_back(move(plane));

	normalTexturedModels.push_back(GetNormalTexturedModelFromOBJ(L"Resources\\box.obj", true));
	NormalTexturedModel model;
	NormalTextureVertexType ntv;
	ntv.normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	ntv.position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
	ntv.tex = XMFLOAT2(0.0f, 1.0f);
	model.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // Top left
	ntv.tex = XMFLOAT2(0.0f, 0.0f);
	model.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // Bottom right.
	ntv.tex = XMFLOAT2(1.0f, 1.0f);
	model.vertices.push_back(ntv);

	ntv.position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
	ntv.tex = XMFLOAT2(1.0f, 0.0f);
	model.vertices.push_back(ntv);

	model.indices.push_back(1);
	model.indices.push_back(2);
	model.indices.push_back(0);

	model.indices.push_back(1);
	model.indices.push_back(3);
	model.indices.push_back(2);

	normalTexturedModels.push_back(move(model));
	normalTexturedModels.push_back(GetNormalTexturedModelFromOBJ(L"Resources\\bath.obj", true));

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

	for (auto &shader : shaders)
		shader->Init(device);

	for (auto &shader : computeShaders)
		shader->Init(device);

	textures.push_back(GetTextureFromFile(L"Resources\\gaben.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\wave.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\concrete.dds", device));
	textures.push_back(GetTextureFromFile(L"Resources\\tree.dds", device));

	for (auto &model : models)
		model.Init(device);
	for (auto &model : texturedModels)
		model.Init(device);
	for (auto &model : normalTexturedModels)
		model.Init(device);
	normalMappedModel.Init(device);
}

ColorModel ResourceManager::GetModelFromOBJ(wstring filename, bool invert)
{
	ColorModel model;
	ifstream in(filename, ios::binary);
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
			model.vertices.emplace_back(x, y, -z);
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
				model.indices.push_back(vertex.vertex);
			}
		}
	}

	return model;
}

NormalModel ResourceManager::GetNormalModelFromOBJ(wstring filename, bool invert)
{
	NormalModel model;
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
			for (auto &vertex : vertices)
			{
				model.vertices[vertex.vertex].normal = normals[vertex.normal];
				model.indices.push_back(vertex.vertex);
			}
		}
	}

	return model;
}

NormalMappedModel ResourceManager::GetNormalMappedModelFromOBJ(wstring filename, bool invert)
{
	NormalMappedModel model;
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
			for (auto &vertex : vertices)
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

TexturedModel ResourceManager::GetTexturedModelFromOBJ(wstring filename, bool unindex, bool invert)
{
	TexturedModel model;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT2> tex;
	vector<TextureVertexType> temp;
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
					model.vertices.push_back(vt);
					model.indices.push_back(model.vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : fvert)
				{
					model.vertices[vertex.vertex].tex = tex[vertex.tex];
					model.indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return model;
}

NormalTexturedModel ResourceManager::GetNormalTexturedModelFromOBJ(wstring filename, bool unindex, bool invert)
{
	NormalTexturedModel model;
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
				model.vertices.emplace_back(x, y, -z);
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
			auto vertices = GetVerticesFromFace(blob);
			if (!invert)
			{
				Utils::Reverse(vertices);
			}
			if (unindex)
			{
				for (auto &vertex : vertices)
				{
					NormalTextureVertexType vt = temp[vertex.vertex];
					vt.tex = tex[vertex.tex];
					vt.normal = normals[vertex.normal];
					model.vertices.push_back(vt);
					model.indices.push_back(model.vertices.size() - 1);
				}
			}
			else
			{
				for (auto &vertex : vertices)
				{
					model.vertices[vertex.vertex].tex = tex[vertex.tex];
					model.vertices[vertex.vertex].normal = normals[vertex.normal];
					model.indices.push_back(vertex.vertex);
				}
			}
		}
	}

	return model;
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