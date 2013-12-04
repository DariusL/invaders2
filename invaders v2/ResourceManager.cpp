#include "includes.h"
#include "ResourceManager.h"
using namespace Microsoft::WRL;

ResourceManager *ResourceManager::handle;

ResourceManager::ResourceManager(void)
:normalModel(GetNormalModelFromOBJ(L"Resources\\ball.obj")),
shader(L"GlobalDiffuseVertex.cso", L"GlobalDiffusePixel.cso")
{
	normalModel.hitbox = XMFLOAT2(1.5f, 1.5f);
	handle = this;
}


ResourceManager::~ResourceManager(void)
{
}

void ResourceManager::Init()
{
}

NormalModel ResourceManager::GetNormalModelFromOBJ(wstring filename, bool invert)
{
	NormalModel model;
	ifstream in(filename, ios::binary);
	vector<XMFLOAT3> normals;
	string input;
	float x, y, z;

	AssertBool(in.is_open(), L"File " + filename + L" not found");

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

vector<ResourceManager::FaceVertex> ResourceManager::GetVerticesFromFace(string &line)
{
	vector<FaceVertex> ret;
	size_t ind1 = 0, ind2 = 0;

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
	size_t ind1 = 0, ind2 = 0;

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

void ResourceManager::InitShaders(ComPtr<ID3D11Device> device)
{
	shader.Init(device);
}