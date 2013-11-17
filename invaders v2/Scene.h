#pragma once
#include "iworld.h"
#include "Globals.h"
#include "SomethingConcurent.h"

class Scene : public IWorld
{
	SomethingConcurent instancer;
public:
	Scene();
	~Scene();

	bool Start();
	void Stop();

	int OnLoop(int input, float frameLength);
	
	void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};