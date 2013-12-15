#pragma once
#include "BaseInstancer.h"

template<class vt, class sh>
class Particles : public BaseInstancer<vt, sh, XMFLOAT3>
{
protected:
	struct Particle
	{
		XMFLOAT3 pos;
		XMFLOAT3 speed;
		Particle(XMFLOAT3 pos = ZeroVec3, XMFLOAT3 speed = ZeroVec3) :pos(pos), speed(speed){}
	};
	const int perSecond;
	const float speed;
	const XMFLOAT3 dir;
	const default_random_engine gen;
	const uniform_real_distribution<float> dist;
	const XMFLOAT3 acc;

	vector<Particle> particles;
	vector<Particle> temp;
public:
	Particles(Model<vt> &model, sh &shader, int maxObjectCount, XMFLOAT3 pos, XMFLOAT3 dir = XMFLOAT3(1.0f, 1.0f, 0.0f), float scatter = 0.5f, float speed = 10.0f, int perSecond = 30);
	Particles(Particles&) = delete;

	void OnLoop(float frame);
};

template<class vt, class sh>
Particles<vt, sh>::Particles(Model<vt> &model, sh &shader, int maxObjectCount, XMFLOAT3 pos, XMFLOAT3 dir, float scatter, float speed, int perSecond)
:BaseInstancer(model, shader, maxObjectCount, pos), dir(dir), perSecond(perSecond), speed(speed), dist(-scatter, scatter), acc(0.0f, -9.8f, 0.0f)
{
}

template<class vt, class sh>
void Particles<vt, sh>::OnLoop(float frame)
{
	int make = int(perSecond * frame);
	if (instanceCount + make > maxInstanceCount)
		make = maxInstanceCount - instanceCount;
	if (make)
	{
		auto num = bind(dist, gen);
		for (int i = 0; i < make; i++)
		{
			XMVECTOR vec = XMVectorSet(num(), 0.0f, num(), 0.0f);
			XMVECTOR dir = vec + XMLoadFloat3(&this->dir);
			dir = XMVector3Normalize(dir) * speed;
			XMFLOAT3 pspeed;
			XMStoreFloat3(&pspeed, dir);
			particles.emplace_back(pos, pspeed);
		}
	}
	instanceData.clear();
	for (auto &particle : particles)
	{
		XMVECTOR pPos = XMLoadFloat3(&particle.pos);
		XMVECTOR pSpeed = XMLoadFloat3(&particle.speed);

		XMVECTOR pNext = pPos + pSpeed * frame + XMLoadFloat3(&acc) * (frame * frame * 0.5f);
		pSpeed = (pNext - pPos) / frame;
		XMStoreFloat3(&particle.pos, pNext);
		XMStoreFloat3(&particle.speed, pSpeed);
		if (particle.pos.y >= pos.y - 1.0f)
		{
			temp.push_back(particle);
			instanceData.push_back(particle.pos);
		}
	}
	instanceCount = instanceData.size();
	particles.clear();
	swap(particles, temp);
}

typedef Particles<VertexType, ColorInstancedShader> ColoredParticles;