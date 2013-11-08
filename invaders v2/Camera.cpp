#include "includes.h"
#include "Camera.h"


Camera::Camera() : up(0.0f, 1.0f, 0.0f), pos(0.0f, 0.0f, 0.0f), forward(0.0f, 0.0f, 1.0f), right(1.0f, 0.0f, 0.0f), modified(true)
{
}

void Camera::RenderMain()
{
	if (modified)
	{
		modified = false;
		auto forward = this->forward + pos;
		D3DXMatrixLookAtLH(&viewMatrix, &pos, &forward, &up);
	}
}

void Camera::Yaw(float angle)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 temp;

	D3DXMatrixRotationAxis(&matrix, &up, angle);
	D3DXVec3Transform(&temp, &right, &matrix);
	right = D3DXVECTOR3(temp);
	D3DXVec3Transform(&temp, &forward, &matrix);
	forward = D3DXVECTOR3(temp);
	modified = true;
}

void Camera::Pitch(float angle)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 temp;

	D3DXMatrixRotationAxis(&matrix, &right, angle);
	D3DXVec3Transform(&temp, &up, &matrix);
	up = D3DXVECTOR3(temp);
	D3DXVec3Transform(&temp, &forward, &matrix);
	forward = D3DXVECTOR3(temp);
	modified = true;
}

void Camera::Roll(float angle)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 temp;

	D3DXMatrixRotationAxis(&matrix, &forward, angle);
	D3DXVec3Transform(&temp, &up, &matrix);
	up = D3DXVECTOR3(temp);
	D3DXVec3Transform(&temp, &right, &matrix);
	right = D3DXVECTOR3(temp);
	modified = true;
}

void Camera::Up(float dist)
{
	pos += dist * up;
	modified = true;
}

void Camera::Right(float dist)
{
	pos += dist * right;
	modified = true;
}

void Camera::Forward(float dist)
{
	pos += dist * forward;
	modified = true;
}

void Camera::Move(float x, float y, float z)
{
	Forward(z);
	Right(x);
	Up(y);
	modified = true;
}