#include "EnterTopBehavior.h"
#include "../entities/Enemy.h"

void EnterTopBehavior::update(Enemy* enemy)
{
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
