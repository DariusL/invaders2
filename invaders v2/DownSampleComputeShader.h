#pragma once
#include "ComputeShader.h"
class DownSampleComputeShader : public ComputeShader
{
public:
	DownSampleComputeShader(wstring cs) :ComputeShader(cs){}
	virtual ~DownSampleComputeShader(){}
};

