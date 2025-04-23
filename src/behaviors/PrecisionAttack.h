#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"
#include "../utils/GameWorld.h"

class PrecisionAttack : public IAttackBehavior
{
public:
	void update(Enemy* enemy) override;

private:
	float bulletDelay = 0.f;
	Player* player;
};