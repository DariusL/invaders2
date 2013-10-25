#pragma once
#include "includes.h"

#ifndef NULL
	#define NULL 0
#endif

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct TextureVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 tex;
};

struct NormalMappedVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
	D3DXVECTOR2 tex;
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;
};

struct NormalVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
};

struct InstanceType
{
	D3DXVECTOR3 position;
};

struct MatrixType
{
	D3DXMATRIX transform;
	D3DXMATRIX move;
};

struct ControlCodes
{
	static const int LEFT  = 1 << 0;
	static const int RIGHT = 1 << 1;
	static const int LEFT_AND_RIGHT = LEFT | RIGHT;
	static const int FIRE  = 1 << 2;
	static const int PAUSE = 1 << 3;
	static const int UP    = 1 << 4;
	static const int DOWN  = 1 << 5;
	static const int PLUS  = 1 << 6;
	static const int MINUS = 1 << 7;
	static const int GLOBAL_DIFF = 1 << 8;
	static const int GLOBAL_SPEC = 1 << 9;
	static const int POINT_DIFF = 1 << 10;
	static const int POINT_SPEC = 1 << 11;
};

struct RenderParams
{
	float brightness;
	D3DXMATRIX transMatrix;
	D3DXVECTOR3 lightPos;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 cameraPos;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
};

struct BufferInfo
{
	unsigned int offset;
	unsigned int stride;
};