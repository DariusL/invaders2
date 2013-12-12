#pragma once
#include "includes.h"
#include "Camera.h"

#ifndef NULL
	#define NULL 0
#endif

template <typename T>
using ComVector = std::vector<Microsoft::WRL::ComPtr<T>>;

extern const DirectX::XMFLOAT3 ZeroVec3;
extern const DirectX::XMFLOAT4 ZeroVec4;
extern const DirectX::XMFLOAT3 OneVec3;
extern const DirectX::XMFLOAT2 ZeroVec2;

struct VertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

struct TextureVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 tex;

	TextureVertexType(){}
	TextureVertexType(float x, float y, float z) :position(x, y, z){}
};

struct NormalTextureVertexType : public TextureVertexType
{
	DirectX::XMFLOAT3 normal;

	NormalTextureVertexType(){}
	NormalTextureVertexType(float x, float y, float z) :TextureVertexType(x, y, z){}
};

struct NormalMappedVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 tex;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT3 binormal;

	NormalMappedVertexType(float x, float y, float z) :position(x, y, z), color(0.0f, 1.0f, 1.0f, 1.0f), tangent(0.0f, 0.0f, 0.0f), binormal(0.0f, 0.0f, 0.0f){}
};

struct NormalVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;

	NormalVertexType(float x, float y, float z) :position(x, y, z), color(1.0f, 0.0f, 0.0f, 1.0f){}
};

struct InstanceType
{
	DirectX::XMFLOAT3 position;
};

struct MatrixType
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

struct InstancedMatrixType
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
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
	static const int MOVE_UP = 1 << 8;
	static const int MOVE_DOWN = 1 << 9;
	static const int MOVE_LEFT = 1 << 10;
	static const int MOVE_RIGHT = 1 << 11;
	static const int MOVE_FORWARD = 1 << 12;
	static const int MOVE_BACK = 1 << 13;
	static const int ROLL_LEFT = 1 << 14;
	static const int ROLL_RIGHT = 1 << 15;
};

__declspec(align(16)) struct RenderParams
{
	DirectX::XMMATRIX reflecMatrix;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
	DirectX::XMFLOAT3 lightPos;
	float brightness;
	DirectX::XMFLOAT4 diffuseColor;
	float waterScale;
	DirectX::XMFLOAT4 clipPlane;
	DirectX::XMFLOAT2 waterTranslation;
	DirectX::XMMATRIX lightView;
	DirectX::XMMATRIX lightProject;
	__declspec(align(16)) Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	__declspec(align(16)) Camera *camera;
	__declspec(align(16)) bool shadowPass;
	__declspec(align(16)) Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shadowMap;
};

struct ReflectionType
{
	DirectX::XMFLOAT4X4 reflection;
	DirectX::XMFLOAT4X4 refraction;
};

struct WaterType
{
	DirectX::XMFLOAT2 waterTranslation;
	float scale;
	float padding;
};

struct BufferInfo
{
	unsigned int offset;
	unsigned int stride;
};

typedef std::function<void(RenderParams&, Camera&)> PrepareFunction;