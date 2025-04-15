#pragma once
#include "IMovementBehavior.h"

class EnterTopBehavior : public IMovementBehavior
{
public:
	void update(Enemy* enemy) override;
	bool isFinished() const override;

private:
	float targetY = 200.f;
	bool finished = false;
};