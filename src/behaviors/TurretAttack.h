#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"

class TurretAttack : public IAttackBehavior
{
public:
	TurretAttack(float delay);
	void update(Enemy* enemy) override;

private:
	float bulletDelay;
	float actualDelay;
	int numberOfBullets = 24;
	int currentBullet = 0;
};