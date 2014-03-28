#include "includes.h"
#include "StringPool.h"
#include "String.h"

StringPool *StringPool::handle;

StringPool::StringPool(ID3D11Device *device)
:device(device)
{
	handle = this;
}

ColorModel &StringPool::GetString(e::string text)
{
	if (stringModels.find(text) == stringModels.end())
	{
		stringModels.emplace(text, ColorModel(device, String<VertexType>(text)));
	}
	return stringModels[text];
}