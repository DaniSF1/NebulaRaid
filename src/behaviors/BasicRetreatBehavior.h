#pragma once
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"

class BasicRetreatBehavior : public IMovementBehavior
{
public:
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;
	void reset() override;

private:
	float targetY = -100.f;
	bool finished = false;
};