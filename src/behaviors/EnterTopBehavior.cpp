#include "EnterTopBehavior.h"

EnterTopBehavior::EnterTopBehavior()
{
}

EnterTopBehavior::EnterTopBehavior(int target)
{
	targetY = target;
}

void EnterTopBehavior::update(Enemy* enemy)
{
	if (!enemy->getActive()) return;
	Vector2 pos = enemy->getWorldPos();
	if (pos.y < targetY) 
	{
		enemy->setWorldPos({ pos.x, pos.y + enemy->getSpeed() * GetFrameTime()});
	}
	else
	{
		finished = true;
	}
}

bool EnterTopBehavior::isFinished() const
{
	return finished;
}

void EnterTopBehavior::newPos(Enemy* enemy)
{
}

void EnterTopBehavior::reset()
{
	finished = false;
}
