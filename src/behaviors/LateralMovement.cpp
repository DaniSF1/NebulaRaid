#include "LateralMovement.h"

void LateralMovement::update(Enemy* enemy)
{
	Vector2 newPosition = Vector2Add(enemy->getWorldPos(), Vector2Scale(direction, enemy->getSpeed() * GetFrameTime()));
	bool passedTarget = (direction.x > 0 && newPosition.x >= targetPos.x) ||
						(direction.x < 0 && newPosition.x <= targetPos.x);

	if (passedTarget)
	{
		enemy->setWorldPos(targetPos);
		newPos(enemy);
	}
	else enemy->setWorldPos(newPosition);

	maxActiveSec -= GetFrameTime();
	if (maxActiveSec <= 0)
	{
		finished = true;
	}
#ifdef DEBUG_MODE
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
#endif
}

bool LateralMovement::isFinished() const
{
	return finished;
}

void LateralMovement::newPos(Enemy* enemy)
{
	targetX = GetRandomValue(10.f, GameConfig::instance().screenWidth - enemy->getWidth() * enemy->getScale());

	targetPos = { targetX, enemy->getWorldPos().y};
	direction = Vector2Normalize(Vector2Subtract(targetPos, enemy->getWorldPos()));
}
