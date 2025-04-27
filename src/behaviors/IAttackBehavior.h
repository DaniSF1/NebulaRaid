#pragma once

class Enemy;

class IAttackBehavior 
{
public:
	virtual void update(Enemy* enemy) = 0;
};