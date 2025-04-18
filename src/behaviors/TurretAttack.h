#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"

class TurretAttack : public IAttackBehavior
{
public:
	void update(Enemy* enemy) override;

private:

};