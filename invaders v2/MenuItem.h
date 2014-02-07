#pragma once
#include "includes.h"
#include "IDrawable.h"

class MenuItem : public virtual IDrawable
{
public:
	virtual ~MenuItem(){}
	virtual bool Loop(int input) = 0;
	virtual void Delay() = 0;
	virtual void Select(bool selected) = 0;
};