#pragma once

#include "includes.h"

class Camera
{
public:
	Camera();

	void Up(float dist);
	void Right(float dist);
	void Forward(float dist);
	void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);
	void Move(DirectX::XMFLOAT3 vec){ Move(vec.x, vec.y, vec.z); }
	void Move(float x, float y, float z);

	const DirectX::XMFLOAT3 &GetPosition() const { return pos; }

	const DirectX::XMMATRIX GetViewMatrix(){ RenderMain(); return XMLoadFloat4x4(&viewMatrix); }
	DirectX::XMMATRIX GetReflectedViewMatrix(const DirectX::XMMATRIX &reflect, const DirectX::XMMATRIX &zeroReflect);

private:
	void RenderMain();

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 up;
	DirectX::XMFLOAT3 right;

	DirectX::XMFLOAT4X4 viewMatrix;
	bool modified;
};
