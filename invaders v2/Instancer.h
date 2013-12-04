#pragma once
#include "BaseInstancer.h"
class Instancer : public SimpleBaseInstancer
{
	vector<Entity> objects;//objektai
	const size_t workerCount;//giju skaicius
	float frame;//paskutinio kadro ilgis

	condition_variable mainWaitCondition;//salgyga pagrindines gijos blokavimui
	condition_variable workerWaitCondition;//salgyga darbiniu giju blokavimui

	mutex mtx;
	atomic<size_t> currentObject;//indeksas sekancio objekto kuri reikia apdoroti

	atomic<int> atStart;//skaicius darbiniu giju esanciu pradzios metode
	volatile bool blockStart;//ar reikia blokuoti gijas pradzioje

	bool stop;//naudojamas baigiant darba
public:
	Instancer(size_t objectCount, float radius, int workerCount);
	virtual ~Instancer(){}

	Entity &GetPhysicsTask(bool &valid);
	IPhysicalInfo &Get(int i){ return objects[i]; }

	float FrameStart();
	void OnLoop(float framelength);
	bool Update(ComPtr<ID3D11DeviceContext> context);

	void Stop();
};