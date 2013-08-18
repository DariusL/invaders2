#pragma once
#include <memory>
#include "IDrawable.h"

class IDrawableGroup : public IDrawable
{
public:
	virtual void AddChild(std::unique_ptr<IDrawable> child) = 0;
};