#pragma once
#pragma warning(disable : 4005)
#include <D3D11.h>
#include <D3DX10math.h>

#ifndef NULL
	#define NULL 0
#endif

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct ControlCodes
{
	static const int LEFT  = 1 << 0;
	static const int RIGHT = 1 << 1;
	static const int LEFT_AND_RIGHT = LEFT | RIGHT;
	static const int FIRE  = 1 << 2;
	static const int PAUSE = 1 << 3;
};

struct COMDeleter {
    template<typename T> void operator()(T* p) {
        p->Release();
    }
};