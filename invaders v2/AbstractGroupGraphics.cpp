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
bool AbstractGroupGraphics::Update(ID3D11DeviceContext*){return true;}