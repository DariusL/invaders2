#pragma once
#include "includes.h"
#include "Model.h"
using namespace Microsoft::WRL;
using namespace std;
class StringPool
{
	unordered_map<string, ColorModel> stringModels;
	ComPtr<ID3D11Device> device;
	static StringPool *handle;
public:
	StringPool(ComPtr<ID3D11Device> device);
	~StringPool(){}
	ColorModel &GetString(string text);
	static StringPool &Get(){ return *handle; }
};

typedef StringPool SP;
