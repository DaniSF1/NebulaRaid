#pragma once
#include "../core/BaseCharacter.h"
#include "Bullet.h"
#include "../core/Pool.h"
#include "raymath.h"

class Enemy : public BaseCharacter
{
public:
	Enemy();
	virtual void tick() override;
	virtual void undoMovement() override;
	virtual void shoot() override;
	~Enemy() override = default;

private:
	bool readyToShoot;
	float bulletDelay; //seconds
	Vector2 targetPos;
	Rectangle movBounds;
	Vector2 direction;
	float length;

	void newPos();
};