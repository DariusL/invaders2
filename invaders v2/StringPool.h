#pragma once
#include "includes.h"
#include "Model.h"
using namespace Microsoft::WRL;
using namespace std;
class StringPool
{
	unordered_map<string, ColorModel> stringModels;
	ID3D11Device *device;
	static StringPool *handle;
public:
	StringPool(ID3D11Device *device);
	~StringPool(){}
	ColorModel &GetString(string text);
	static StringPool &Get(){ return *handle; }
};

typedef StringPool SP;
