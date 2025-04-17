#pragma once
#include "../core/BaseCharacter.h"
#include "../utils/GameConfig.h"
#include "../behaviors/IMovementBehavior.h"
#include "../behaviors/IAttackBehavior.h"
#include "../behaviors/EnterTopBehavior.h"
#include "../behaviors/RandomMovement.h"
#include "../behaviors/BasicAttackBehavior.h"
#include "../behaviors/BasicRetreatBehavior.h"
#include "Bullet.h"
#include "raymath.h"

enum class EnemyState
{
	Entering,
	Active,
	Retreating
};

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
	static Texture2D sharedTexture;
	static Texture2D sharedBulletTexture;
	EnemyState state = EnemyState::Entering;

	IAttackBehavior* attackBehavior;
	IMovementBehavior* movementBehavior;
};