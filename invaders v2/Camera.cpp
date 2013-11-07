#include "includes.h"
#include "Camera.h"


Camera::Camera() : up(0.0f, 1.0f, 0.0f), pos(0.0f, 0.0f, 0.0f), forward(0.0f, 0.0f, 1.0f), right(1.0f, 0.0f, 0.0f)
{
}

void Camera::RenderMain()
{
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &forward, &up);
}

void Camera::RenderMirror()
{
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 1.0f, 1.0f, -1.0f);
	D3DXVECTOR4 temp;
	D3DXVec3Transform(&temp, &this->pos, &scale);
	D3DXVECTOR3 pos(temp);
	D3DXVec3Transform(&temp, &this->forward, &scale);
	D3DXVECTOR3 forward(temp);
	D3DXVec3Transform(&temp, &this->up, &scale);
	D3DXVECTOR3 up(temp);
	D3DXMatrixLookAtLH(&mirrorMatrix, &pos, &forward, &up);
}


void Camera::Yaw(float angle)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 temp;
	auto vec = (up - pos);

	D3DXMatrixRotationAxis(&matrix, &vec, angle);
	D3DXVec3Transform(&temp, &right, &matrix);
	right = D3DXVECTOR3(temp);
	D3DXVec3Transform(&temp, &forward, &matrix);
	forward = D3DXVECTOR3(temp);
}

void Camera::Pitch(float angle)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 temp;
	auto vec = (right - pos);

	D3DXMatrixRotationAxis(&matrix, &vec, angle);
	D3DXVec3Transform(&temp, &up, &matrix);
	up = D3DXVECTOR3(temp);
	D3DXVec3Transform(&temp, &forward, &matrix);
	forward = D3DXVECTOR3(temp);
}

void Camera::Up(float dist)
{
	auto vec = dist * (up - pos);
	pos += vec;
	right += vec;
	forward += vec;
}

void Camera::Right(float dist)
{
	auto vec = dist * (right - pos);
	pos += vec;
	up += vec;
	forward += vec;
}

void Camera::Forward(float dist)
{
	auto vec = dist * (forward - pos);
	pos += vec;
	right += vec;
	up += vec;
}

void Camera::Move(D3DXVECTOR3 offset)
{
	pos += offset;
	right += offset;
	up += offset;
	forward += offset;
}