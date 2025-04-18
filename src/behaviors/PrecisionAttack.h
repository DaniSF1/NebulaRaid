#pragma once
#include "IAttackBehavior.h"
#include "../entities/Enemy.h"

class PrecisionAttack : public IAttackBehavior
{
public:
	void update(Enemy* enemy) override;

private:

};