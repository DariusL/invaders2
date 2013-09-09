#include "Camera.h"


Camera::Camera()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::SetTarget(float x, float y, float z)
{
	target = D3DXVECTOR3(x, y, z);
}

void Camera::SetPosition(float x, float y, float z)
{
	pos = D3DXVECTOR3(x, y, z);
}

void Camera::SetRotation(float x, float y, float z)
{
	rot = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR3 Camera::GetPosition()
{
	return pos;
}

D3DXVECTOR3 Camera::GetRotation()
{
	return rot;
}

void Camera::Render()
{
	D3DXVECTOR3 up, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// Setup where the camera is looking by default.

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rot.x * 0.0174532925f;
	yaw   = rot.y * 0.0174532925f;
	roll  = rot.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &target, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &lookAt, &up);
}

void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = this->viewMatrix;
}