#pragma once
#include "IDrawable.h"

class IDrawableObject : public IDrawable
{
protected:
	virtual bool InitBuffers(ID3D11Device*) = 0;
	virtual void SetBuffers(ID3D11DeviceContext*) = 0;
	virtual bool Update(ID3D11DeviceContext*) = 0;
};