#pragma once

#include "includes.h"
#include "InstanceEntity.h"
#include "Model.h"

typedef unsigned int UINT;

namespace Utils{
	//returns a new array with the contents of the file
	bool ReadFileToArray(std::string file, std::unique_ptr<char> &arr, UINT &size);
	//return fractional part, ret + trunced = x
	float Trunc(float x, float &trunced);
	std::vector<InstanceEntity> GetGrid(int width, int height, D3DXVECTOR3 center, D3DXVECTOR2 gap, ColorModel &model);
	void ShowMessageBox(wstring text, wstring title);
	D3DXPLANE PlaneFromPointAndRot(D3DXVECTOR3 point, D3DXVECTOR3 rot);

	template<class T>
	void VectorAppend(std::vector<T> &dest, const std::vector<T> &source)
	{
		dest.insert(dest.end(), source.begin(), source.end());
	}

	template<class T>
	void CopyToBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer, const T &data, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &data, sizeof(T));
		context->Unmap(buffer.Get(), 0);
	}

	template<class T>
	void Reverse(std::vector<T> &vec)
	{
		reverse(vec.begin(), vec.end());
	}
}

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define __WFILE__ WIDE1(__FILE__)

#ifndef _DEBUG
#define Assert(x)   if (x != S_OK) \
                        { \
							wstringstream stream; \
							stream << hex << x; \
							Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
							exit(-1); \
                        }
#else
#define Assert(x)   if (x != S_OK) \
						{ \
							wstringstream stream; \
							stream << hex << x; \
							Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
							DebugBreak(); \
						}
#endif