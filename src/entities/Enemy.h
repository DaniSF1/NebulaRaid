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
	~Enemy() override = default;
	void tick() override;
	void undoMovement() override;
	void shoot() override;
	static void LoadSharedTexture();
	static void UnloadSharedTexture();

private:
	bool readyToShoot;
	float bulletDelay; //seconds
	Vector2 targetPos;
	Rectangle movBounds;
	Vector2 direction;
	float length;
	static Texture2D sharedTexture;
	static Texture2D sharedBulletTexture;

	void newPos();
};