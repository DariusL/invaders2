#pragma once
#include "ComputeShader.h"

class CopyComputeShader : public ComputeShader
{
public:
	CopyComputeShader(wstring cs) : ComputeShader(cs){}
	virtual ~CopyComputeShader(){}
};