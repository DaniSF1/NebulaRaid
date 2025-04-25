#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "../utils/GameWorld.h"

class BerserkerAttack : public IAttackBehavior
{
public:
	BerserkerAttack(float delay);
	void update(Enemy* enemy) override;

private:
	Player* player;
	float bulletDelay;
	float actualDelay;
	float burstCooldown;
	int burstCount;
	Vector2 direction;

	void precisionShot(Enemy* enemy);
	void circularShot(Enemy* enemy, int bullets);
};