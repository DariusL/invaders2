#pragma once
#include "BaseInstancer.h"
class Instancer : public SimpleBaseInstancer
{
	vector<Entity> objects;
	const size_t workerCount;
	float frame;

	condition_variable mainWaitCondition;
	condition_variable workerWaitCondition;

	mutex mtx;
	atomic<int> currentObject;

	atomic<int> atStart;
	volatile bool blockStart;

	bool stop;
public:

	Instancer(size_t objectCount, float radius, int workerCount);
	virtual ~Instancer();

	Entity &GetPhysicsTask(bool &valid);
	IPhysicalInfo &Get(int i){ return objects[i]; }

	float FrameStart();
	void OnLoop(float framelength);
	bool Update(ComPtr<ID3D11DeviceContext> context);

	void Stop();
};