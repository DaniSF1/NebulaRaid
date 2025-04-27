#pragma once
#include "../behaviors/IAttackBehavior.h"
#include "../entities/Enemy.h"

class BasicAttackBehavior : public IAttackBehavior
{
public:
	BasicAttackBehavior(float delay);
	void update(Enemy* enemy) override;

private:
	float bulletDelay;
	float actualDelay;
};