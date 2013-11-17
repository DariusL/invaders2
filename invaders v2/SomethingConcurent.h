#pragma once
#include "IDrawable.h"
#include "Instancer.h"
class SomethingConcurent : public IDrawable
{
	Instancer instancer;
	vector<thread> workers;
public:
	SomethingConcurent(int objectCount, float radius, int threadCount);
	~SomethingConcurent();

	void Init(ComPtr<ID3D11Device> device){ instancer.Init(device); }
	void Render(const RenderParams& params){ instancer.Render(params); }
	void OnLoop(float framelength);
private:
	static void Worker(Instancer &instancer, int objectCount);
	static XMVECTOR XM_CALLCONV Acceleration(XMVECTOR subject, XMVECTOR target, float targetMass);
	static volatile bool doWork;
};