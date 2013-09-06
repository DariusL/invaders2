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

	float speed;
	float deathTime;
	bool dead;
public:
	Entity();
	Entity(D3DXVECTOR3 start, D3DXVECTOR2 size);
	Entity(D3DXVECTOR3 start, D3DXVECTOR2 size, float speed);
	virtual ~Entity(void);

	D3DXVECTOR3 GetPos() const {return pos;}
	void MoveBy(D3DXVECTOR3 step);
	void MoveTo(D3DXVECTOR3 pos);

	float GetLeftBorder() const {return pos.x - size.x / 2;}
	float GetRightBorder() const {return pos.x + size.x / 2;}
	float GetTopBorder() const {return pos.y + size.y / 2;}
	float GetBottomBorder() const {return pos.y - size.y / 2;}

	void SetSpeed(float speed){this->speed = speed;}
	float GetSpeed() const {return speed;}

	float GetDeathTime() const {return deathTime;}

	bool IsDead() const {return dead;}
	void Kill();
	void Revive(){dead = false;}
	
	bool CollidesWith(const Entity &other) const;
};

