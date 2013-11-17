#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(int objectCount, float radius)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount)
{
	default_random_engine gen;
	uniform_real_distribution<float> dist(-10.0f, 10.0f);
	auto num = bind(dist, gen);
	for (int i = 0; i < objectCount; i++)
	{
		XMVECTOR vec = XMVectorSet(num(), num(), num(), 0.0f);
		vec = XMVector3Normalize(vec) * radius;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, vec);
		objects.emplace_back(pos);
	}
}

Instancer::~Instancer()
{
}

bool Instancer::Update(ComPtr<ID3D11DeviceContext> context)
{
	instanceCount = objects.size();
	for (int i = 0; i < instanceCount; i++)
		instanceData[i] = objects[i].GetPos();
	return BaseInstancer::Update(context);
}