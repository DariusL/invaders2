#pragma once
#pragma warning(disable : 4005)
#include <D3D11.h>
#include <D3DX10math.h>
#include <ctime>
class Entity
{
protected:
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;

	//per second
	double fireRate;
	double lastFired;
public:
	Entity();
	Entity(D3DXVECTOR3 start, D3DXVECTOR2 size);
	~Entity(void);

	D3DXVECTOR3 GetPos(){return pos;}
	void MoveBy(D3DXVECTOR3 step);

	float GetLeftBorder() const {return pos.x - size.x / 2;}
	float GetRightBorder() const {return pos.x + size.x / 2;}
	float GetTopBorder() const {return pos.y + size.y / 2;}
	float GetBottomBorder() const {return pos.y - size.y / 2;}

	void SetFireRate(double fireRate){this->fireRate = fireRate;}
	double GetFireRate(){return fireRate;}

	void Fire(){lastFired = std::clock() / double(CLOCKS_PER_SEC);}
	double GetLastFired(){return lastFired;}
};

