#pragma once 
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"

enum class LateralMovementMode 
{
	Left,
	Right
};

class StaticMovement : public IMovementBehavior
{
public:
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;
	void reset() override;

private:
	bool finished = false;
	float maxActiveSec = 30.f;

	Vector2 targetPos, direction;
	LateralMovementMode mode = LateralMovementMode::Right;
	bool initialized = false;
};