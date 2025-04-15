#pragma once

class Enemy;

class IMovementBehavior
{
public:
	virtual void update(Enemy* enemy) = 0;
	virtual bool isFinished() const = 0;
};