#pragma once
#include "DoubleInputComputeShader.h"
class TexelSumComputeShader : public DoubleInputComputeShader
{
public:
	TexelSumComputeShader(e::wstring cs) : DoubleInputComputeShader(cs){}
	virtual ~TexelSumComputeShader(){}
};

