#pragma once 
#include "IMovementBehavior.h"
#include "../entities/Enemy.h"

class RandomMovement : public IMovementBehavior
{
public:
	void update(Enemy* enemy) override;
	bool isFinished() const override;
	void newPos(Enemy* enemy) override;

private:
	bool finished = false;
	float maxActiveSec = 20.f;

	Rectangle movBounds = { 0.f, 0.f, 720.f, 400.f };
	Vector2 targetPos, direction;
};