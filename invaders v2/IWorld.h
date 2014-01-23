#pragma once

#include "IDrawable.h"
#include "Camera.h"
#include "Level.h"
#include "Light.h"

using namespace std;
using namespace Microsoft::WRL;

class IWorld : public IDrawable
{
protected:
	Camera camera;
	
public:
	IWorld(){}
	virtual ~IWorld(){}

	virtual int OnLoop(int input, float frameLength) = 0;

	Camera &GetCamera(){return camera;}

	enum Result
	{
		CONTINUE,
		GAME_OVER,
		NEXT_LEVEL
	};
};