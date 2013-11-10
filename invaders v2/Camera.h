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
	void Move(XMFLOAT3 vec){ Move(vec.x, vec.y, vec.z); }
	void Move(float x, float y, float z);

	XMFLOAT3 GetPosition() const {return pos;}

	const XMMATRIX GetViewMatrix(){ RenderMain(); return XMLoadFloat4x4(&viewMatrix); }
	XMMATRIX GetReflectedViewMatrix(const XMMATRIX &reflect, const XMMATRIX &zeroReflect);

private:
	void RenderMain();

	XMFLOAT3 pos;
	XMFLOAT3 forward;
	XMFLOAT3 up;
	XMFLOAT3 right;

	XMFLOAT4X4 viewMatrix;
	bool modified;
};
