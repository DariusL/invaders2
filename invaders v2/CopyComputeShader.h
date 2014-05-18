#pragma once
#include "ComputeShader.h"

class CopyComputeShader : public ComputeShader
{
public:
	CopyComputeShader(e::wstring cs) : ComputeShader(cs){}
	virtual ~CopyComputeShader(){}
};