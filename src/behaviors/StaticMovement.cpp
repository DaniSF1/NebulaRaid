#include "StaticMovement.h"

void StaticMovement::update(Enemy* enemy)
{
	if (enemy->getHealth() <= 40)
	{
		if (!initialized)
		{
			newPos(enemy);
			initialized = true;
		}

		Vector2 newPosition = Vector2Add(enemy->getWorldPos(), Vector2Scale(direction, enemy->getSpeed() * GetFrameTime()));
		enemy->setWorldPos(newPosition);
	}

	maxActiveSec -= GetFrameTime();
	if (maxActiveSec <= 0)
	{
		finished = true;
	}
#ifdef DEBUG_MODE
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
#endif
}

bool StaticMovement::isFinished() const
{
	return finished;
}

void StaticMovement::newPos(Enemy* enemy)
{
	if (mode == LateralMovementMode::Right)
	{
		targetPos = { GameConfig::instance().screenWidth - enemy->getWidth() * enemy->getScale(), enemy->getWorldPos().y };
		mode = LateralMovementMode::Left;
	}
	else
	{
		targetPos = { 10.f, enemy->getWorldPos().y };
		mode = LateralMovementMode::Right;
	}

	direction = Vector2Normalize(Vector2Subtract(targetPos, enemy->getWorldPos()));
}
