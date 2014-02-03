#pragma once
#include "includes.h"
using namespace Microsoft::WRL;
class IPass
{
	virtual void Pass(ID3D11DeviceContext *context, ID3D11ShaderResourceView *input, ID3D11UnorderedAccessView *output) = 0;
};