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
	void draw(Color tint) override;
	void undoMovement() override;
	void shoot(Vector2 dir) override;
	void takeDamage(int damage) override;
	bool isDamaged() const { return activeDamaged > 0.0f; }

	void setEnterBehavior(IMovementBehavior* enter) { enterBehavior = enter; }
	void setMovementBehavior(IMovementBehavior* movement) { movementBehavior = movement; }
	void setRetreatBehavior(IMovementBehavior* retreat) { retreatBehavior = retreat; }
	void setAttackBehavior(IAttackBehavior* attack) { attackBehavior = attack; }

	static void LoadSharedTexture();
	static void UnloadSharedTexture();

private:
	static Texture2D sharedTexture;
	static Texture2D sharedBulletTexture;
	EnemyState state = EnemyState::Entering;

	IMovementBehavior* enterBehavior;
	IAttackBehavior* attackBehavior;
	IMovementBehavior* movementBehavior;
	IMovementBehavior* retreatBehavior;

	float activeDamaged = 0.f;
	const float maxDamaged = 0.5f;
};