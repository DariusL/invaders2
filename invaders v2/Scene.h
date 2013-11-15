#pragma once
#include "iworld.h"
#include "Globals.h"

class Scene : public IWorld
{
	
public:
	Scene();
	~Scene();

	bool Start(shared_ptr<Level> level);
	void Stop();

	int OnLoop(int input, float frameLength);
	
	void Init(ComPtr<ID3D11Device> device);
	void Render(const RenderParams &params);
};