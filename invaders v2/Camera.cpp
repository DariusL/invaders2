#include "Camera.h"


Camera::Camera()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	yaw = 0.0f;
	pitch = 0.0f;
}

void Camera::SetPosition(const D3DXVECTOR3& pos)
{
	//this->pos = pos;
}

void Camera::SetRotation(float yaw, float pitch, float r)
{
	this->yaw = yaw;
	this->pitch = pitch;
	this->r = r;
}

void Camera::Render()
{
	D3DXVECTOR3 up, lookAt;
	D3DXMATRIX pitchMatrix;
	D3DXMATRIX yawMatrix;

	// Setup the vector that points upwards.
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	lookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, -r);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0.0f);
	D3DXMatrixRotationX(&pitchMatrix, pitch);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &pitchMatrix);
	D3DXVec3TransformCoord(&up, &up, &pitchMatrix);
	D3DXVec3TransformCoord(&pos, &pos, &pitchMatrix);

	D3DXMatrixRotationAxis(&yawMatrix, &up, yaw);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &yawMatrix);
	D3DXVec3TransformCoord(&pos, &pos, &yawMatrix);

	lookAt = pos + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &lookAt, &up);
}

void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = this->viewMatrix;
}