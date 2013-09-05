#pragma once
#include "IDrawable.h"

class IDrawableObject : public IDrawable
{
protected:
	virtual bool InitBuffers(ComPtr<ID3D11Device>) = 0;
	virtual void SetBuffers(ComPtr<ID3D11DeviceContext>) = 0;
	virtual bool Update(ComPtr<ID3D11DeviceContext>) = 0;
};