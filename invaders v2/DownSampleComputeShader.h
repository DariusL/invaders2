#pragma once
#include "ComputeShader.h"
class DownSampleComputeShader : public ComputeShader
{
public:
	DownSampleComputeShader(e::wstring cs) :ComputeShader(cs){}
	virtual ~DownSampleComputeShader(){}
};

