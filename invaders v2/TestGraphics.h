#pragma once
#include "playergraphics.h"
class TestGraphics : public PlayerGraphics
{
public:
	TestGraphics(void);
	~TestGraphics(void);
protected:
	void Update(ID3D11DeviceContext*);
};

