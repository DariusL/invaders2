#pragma once

#include "includes.h"
#include "WaterShader.h"
#include "Mirror.h"

class WaterPlane : public Mirror<TextureVertexType, WaterShader>
{
	
};