#include "BasicRetreatBehavior.h"

void BasicRetreatBehavior::update(Enemy* enemy)
{
	Vector2 pos = enemy->getWorldPos();
	if (pos.y > targetY)
	{
		enemy->setWorldPos({ pos.x, pos.y - enemy->getSpeed() * GetFrameTime() });
	}
	else
	{
		finished = true;
	}
}

bool BasicRetreatBehavior::isFinished() const
{
	return finished;
}

void BasicRetreatBehavior::newPos(Enemy* enemy)
{
}
