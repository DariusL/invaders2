#pragma once
#include "ComputeShader.h"
class UpSampleComputeShader : public ComputeShader
{
public:
	UpSampleComputeShader(wstring cs) :ComputeShader(cs){}
	virtual ~UpSampleComputeShader(){}
};