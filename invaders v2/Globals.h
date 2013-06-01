#pragma once
#pragma warning(disable : 4005)
#include <D3D11.h>
#include <D3DX10math.h>

#ifndef NULL
	#define NULL 0
#endif

static void* AppHandle = 0;

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct ControlCodes
{
	static const int LEFT  = 1 << 0;
	static const int RIGHT = 1 << 1;
	static const int FIRE  = 1 << 2;
	static const int PAUSE = 1 << 3;
};