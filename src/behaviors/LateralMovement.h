#pragma once
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"

class LateralMovement : public IMovementBehavior
{
public:
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;

private:

};