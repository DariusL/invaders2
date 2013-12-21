#pragma once
#include "includes.h"
using namespace Microsoft::WRL;
class IPass
{
	virtual void Pass(ComPtr<ID3D11DeviceContext> context, ComPtr<ID3D11ShaderResourceView> input, ComPtr<ID3D11UnorderedAccessView> output) = 0;
};