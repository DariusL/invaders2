#pragma once
#include "camera.h"
#include "IDrawableObject.h"
class FloatingCamera : public Camera, public IDrawableObject
{
public:
	FloatingCamera(void);
	~FloatingCamera(void);
};

