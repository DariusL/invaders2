#pragma once
#include "graphicsobject.h"
class AbstractGroupGraphics :
	public GraphicsObject
{
public:
	AbstractGroupGraphics(void);
	~AbstractGroupGraphics(void);

protected:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void SetBuffers(ID3D11DeviceContext*);
	void Update(ID3D11DeviceContext*);
};

