#pragma once
#include "includes.h"
#include "IDrawable.h"

class MenuItem
{
public:
	virtual ~MenuItem(){}
	virtual bool Loop(int input) = 0;
};