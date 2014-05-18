#pragma once
#include "DoubleInputComputeShader.h"
class TexelSumComputeShader : public DoubleInputComputeShader
{
public:
	TexelSumComputeShader(wstring cs) : DoubleInputComputeShader(cs){}
	virtual ~TexelSumComputeShader(){}
};

