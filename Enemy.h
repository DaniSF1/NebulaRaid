#pragma once
#include "BaseCharacter.h"
#include "EnemyBullet.h"
#include "Pool.h"
#include "raymath.h"

class Enemy : public BaseCharacter
{
public:
	Enemy();
	virtual void tick() override;
	virtual void shoot() override;

private:
	Pool<EnemyBullet> bulletPool;
	bool readyToShoot;
	float bulletDelay; //seconds
	Vector2 targetPos;
	Rectangle movBounds;
	Vector2 direction;
	float length;

	void newPos();
};