#pragma once
#include "../core/BaseCharacter.h"
#include "../core/Pool.h"
#include "../utils/GameConfig.h"
#include "Bullet.h"
#include "raymath.h"

class Enemy : public BaseCharacter
{
public:
	Enemy();
	void tick() override;
	void undoMovement() override;
	void shoot() override;
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