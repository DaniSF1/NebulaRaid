#include "RandomMovement.h"

void RandomMovement::update(Enemy* enemy)
{
	if (!enemy->getActive()) return;
	enemy->setWorldPos(Vector2Add(enemy->getWorldPos(), Vector2Scale(direction, enemy->getSpeed() * GetFrameTime())));
	if (Vector2DistanceSqr(enemy->getWorldPos(), targetPos) < 10.f) newPos(enemy);

	maxActiveSec -= GetFrameTime();
	if (maxActiveSec <= 0)
	{
		finished = true;
	}
#ifdef DEBUG_MODE
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
#endif
}

bool RandomMovement::isFinished() const
{
	return finished;
}

void RandomMovement::newPos(Enemy* enemy)
{
	targetPos = { movBounds.x + GetRandomValue(0, movBounds.width), movBounds.y + GetRandomValue(0, movBounds.height) };
	direction = Vector2Normalize(Vector2Subtract(targetPos, enemy->getWorldPos()));
}

void RandomMovement::reset()
{
	finished = false;
	maxActiveSec = 20.f;
}
