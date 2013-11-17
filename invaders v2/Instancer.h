#pragma once
#include "BaseInstancer.h"
class Instancer : public SimpleBaseInstancer
{
	vector<Entity> objects;
	const int workerCount;

	condition_variable mainWaitCondition;
	condition_variable workerWaitCondition;
	volatile bool calculating;

	mutex mtx;
	condition_variable distributeCondition;
	volatile bool distributingJobs;
	int currentObject;

	condition_variable barrierCondition;
	atomic<int> passed;
public:
	struct Physicsjob
	{
		Entity &entity;
		bool valid;
	};

	Instancer(int objectCount, float radius, int workerCount);
	virtual ~Instancer();

	virtual bool Update(ComPtr<ID3D11DeviceContext> context);
	Entity &GetPhysicsTask(bool &valid);
	IPhysicalInfo &Get(int i){ return objects[i]; }

	void FrameStart();
	void Barrier();
	void Done();
};