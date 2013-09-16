#pragma once
#pragma warning(disable : 4005)

#include "Shooter.h"
#include "IDrawableObject.h"
#include "Model.h"
#include "ColorShader.h"
#include "includes.h"

using namespace std;
class DrawableShooter : public Shooter, public IDrawableObject
{
	//grafiks
	shared_ptr<Model> model;
	D3DXMATRIX moveMatrix;
	shared_ptr<ColorShader> shader;

	ComPtr<ID3D11Buffer> vertexBuffer;
	BufferInfo vertexInfo;
	ComPtr<ID3D11Buffer> indexBuffer;
public:
	DrawableShooter(float speed, float fireRate, shared_ptr<Model> model);
	virtual ~DrawableShooter(void);

	bool Init(ComPtr<ID3D11Device>);
	void Render(RenderParams);
private:
	bool InitBuffers(ComPtr<ID3D11Device>);
	void SetBuffers(ComPtr<ID3D11DeviceContext>);
	bool Update(ComPtr<ID3D11DeviceContext>);
};