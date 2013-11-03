#include "includes.h"
#include "Camera.h"


Camera::Camera()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Render()
{
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	float radians = rot.y * 0.0174532925f;

	D3DXVECTOR3 lookAt(sinf(radians) + pos.x, pos.y, cosf(radians) + pos.z);

	D3DXMatrixLookAtLH(&viewMatrix, &pos, &lookAt, &up);
}

void Camera::RenderMirror()
{
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	float radians = rot.y * 0.0174532925f;

	D3DXVECTOR3 lookAt(sinf(radians) + pos.x, -pos.y, cosf(radians) + pos.z);

	D3DXMatrixLookAtLH(&mirrorMatrix, &pos, &lookAt, &up);
}