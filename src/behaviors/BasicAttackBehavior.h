#pragma once
#include "../behaviors/IAttackBehavior.h"
#include "../entities/Enemy.h"

class BasicAttackBehavior : public IAttackBehavior
{
public:
	void update(Enemy* enemy) override;

private:
	float bulletDelay = 0.f;
};