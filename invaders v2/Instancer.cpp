#include "includes.h"
#include "Instancer.h"
#include "ResourceManager.h"

Instancer::Instancer(int objectCount)
:BaseInstancer(RM::Get().GetNormalModel(), RM::Get().GetShader(), objectCount)
{
}

Instancer::~Instancer()
{
}

bool Instancer::Update(ComPtr<ID3D11DeviceContext> context)
{

}