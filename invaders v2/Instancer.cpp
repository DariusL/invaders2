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
