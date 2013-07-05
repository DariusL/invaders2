#include "AbstractGroupGraphics.h"


AbstractGroupGraphics::AbstractGroupGraphics(void)
{
}


AbstractGroupGraphics::~AbstractGroupGraphics(void)
{
}

bool AbstractGroupGraphics::InitBuffers(ID3D11Device*){return false;}
void AbstractGroupGraphics::ShutdownBuffers(){}
void AbstractGroupGraphics::SetBuffers(ID3D11DeviceContext*){}
void AbstractGroupGraphics::Update(ID3D11DeviceContext*){}