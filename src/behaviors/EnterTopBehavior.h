#pragma once
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"

class EnterTopBehavior : public IMovementBehavior
{
public:
	EnterTopBehavior();
	EnterTopBehavior(int target);
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;

private:
	float targetY = 200.f;
	bool finished = false;
};