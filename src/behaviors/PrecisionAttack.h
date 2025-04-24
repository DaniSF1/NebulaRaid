#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"
#include "../utils/GameWorld.h"

class PrecisionAttack : public IAttackBehavior
{
public:
	PrecisionAttack(float delay);
	void update(Enemy* enemy) override;

private:
	float bulletDelay;
	float actualDelay;
	Player* player;
};