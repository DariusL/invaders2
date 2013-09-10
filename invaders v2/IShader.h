#pragma once

#include <wrl\client.h>
#include "Globals.h"

using namespace Microsoft::WRL;

class IShader
{
public:
	virtual bool Init(ComPtr<ID3D11Device> device) = 0;

protected:
	virtual bool InitializeShader(ComPtr<ID3D11Device> device, char* vsFilename, char* psFilename) = 0;
};