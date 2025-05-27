#pragma once
#include "../core/BaseCharacter.h"
#include "../utils/GameConfig.h"
#include "../utils/GameWorld.h"
#include "../behaviors/IMovementBehavior.h"
#include "../behaviors/IAttackBehavior.h"
#include "../behaviors/BerserkerMovementMode.h"
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
	Enemy(size_t bulletCount);
	~Enemy() override = default;
	void tick() override;
	void draw(Color tint) override;
	void undoMovement() override;
	void shoot(Vector2 dir) override;
	void takeDamage(int damage) override;
	bool isDamaged() const { return activeDamaged > 0.0f; }
	float getDamage() { return damage; }
	void setDamage(float newDamage) { damage = newDamage; }
	float getBulletSpeed() { return bulletSpeed; }
	void setBulletSpeed(float newBulletSpeed) { bulletSpeed = newBulletSpeed; }
	int getScore() { return score; }
	void setScore(int newScore) { score = newScore; }
	std::string getType() { return type; }
	void setType(std::string newType) { type = newType; }
	int getMaxHealth() { return maxHealth; }
	void setMaxHealth(int newMax) { maxHealth = newMax; }
	void resetState() 
	{ 
		state = EnemyState::Entering; 
		health = maxHealth;
		runningTime = 0.f;
		frame = 0;
		activeDamaged = 0;
		enterBehavior->reset();
		movementBehavior->reset();
		retreatBehavior->reset();
	}

	void setEnterBehavior(IMovementBehavior* enter) { enterBehavior = enter; }
	void setMovementBehavior(IMovementBehavior* movement) { movementBehavior = movement; }
	void setRetreatBehavior(IMovementBehavior* retreat) { retreatBehavior = retreat; }
	void setAttackBehavior(IAttackBehavior* attack) { attackBehavior = attack; }
	BerserkerMovementMode getCurrentMovementMode() const;

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
	float damage = 0.f;
	float bulletSpeed = 0.f;
	int score = 0.f;
	int maxHealth = 0.f;

	std::string type;
};