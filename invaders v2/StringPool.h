#pragma once
#include "includes.h"
#include "Model.h"
class StringPool
{
	e::unordered_map<e::string, ColorModel> stringModels;
	ID3D11Device *device;
	static StringPool *handle;
public:
	StringPool(ID3D11Device *device);
	~StringPool(){}
	ColorModel &GetString(e::string text);
	static StringPool &Get(){ return *handle; }
};

typedef StringPool SP;
