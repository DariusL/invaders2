#pragma once

#include "includes.h"
#include "Globals.h"

typedef unsigned int UINT;

namespace Utils{
	//returns a new array with the contents of the file
	bool ReadFileToArray(std::wstring file, std::unique_ptr<char> &arr, UINT &size);
	//return fractional part, ret + trunced = x
	float Trunc(float x, float &trunced);
	void ShowMessageBox(std::wstring text, std::wstring title);
	e::XMFLOAT4 PlaneFromPointAndRot(e::XMFLOAT3 point, e::XMFLOAT3 rot, bool reverse = false);
	e::XMFLOAT2 GetVec2(float value);
	e::XMFLOAT3 GetVec3(float value);
	e::XMFLOAT4 GetVec4(float value);
	void VectorAdd(e::XMFLOAT3 &target, const e::XMFLOAT3 &off);
	e::XMVECTOR VectorFill(float f);

	e::XMVECTOR VectorSet();
	e::XMVECTOR VectorSet(float x);
	e::XMVECTOR VectorSet(float x, float y);
	e::XMVECTOR VectorSet(float x, float y, float z);

	template<class T>
	void VectorAppend(std::vector<T> &dest, const std::vector<T> &source)
	{
		dest.insert(dest.end(), source.begin(), source.end());
	}

	template<class T>
	void CopyToBuffer(ID3D11Buffer *buffer, const T &data, ID3D11DeviceContext *context)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &data, sizeof(T));
		context->Unmap(buffer, 0);
	}

	template<class T>
	void CopyToBuffer(ID3D11Buffer *buffer, ID3D11DeviceContext *context, const e::vector<T> &data, uint count)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, data.data(), sizeof(T) * count);
		context->Unmap(buffer, 0);
	}

	template<class T>
	void Reverse(std::vector<T> &vec)
	{
		reverse(vec.begin(), vec.end());
	}

	template<class T, class F>
	void RemoveIf(e::vector<T> &vec, F &&cond)
	{
		auto end = e::remove_if(vec.begin(), vec.end(), e::forward<F>(cond));
		vec.resize(end - vec.begin());
	}
}

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define __WFILE__ WIDE1(__FILE__)

#ifndef _DEBUG
#define Assert(x) \
	if (x != S_OK) \
	{ \
		std::wstringstream stream; \
		stream << std::hex << x; \
		Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + std::wstring(L": ") + std::to_wstring(__LINE__)); \
		exit(-1); \
	}
#else
#define Assert(x) \
	if (x != S_OK) \
	{ \
		std::wstringstream stream; \
		stream << std::hex << x; \
		Utils::ShowMessageBox(L"Error number 0x" + stream.str(), __WFILE__ + std::wstring(L": ") + std::to_wstring(__LINE__)); \
		DebugBreak(); \
	}
#endif

#ifndef _DEBUG
#define AssertBool(x, error) \
	if (x != true) \
	{ \
		Utils::ShowMessageBox(error, __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
		exit(-1); \
	}
#else
#define AssertBool(x, error) \
	if (x != true) \
	{ \
		Utils::ShowMessageBox(error, __WFILE__ + wstring(L": ") + to_wstring(__LINE__)); \
		DebugBreak(); \
	}
#endif