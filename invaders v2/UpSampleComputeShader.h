#pragma once
#include "ComputeShader.h"
class UpSampleComputeShader : public ComputeShader
{
public:
	UpSampleComputeShader(e::wstring cs) :ComputeShader(cs){}
	virtual ~UpSampleComputeShader(){}
};