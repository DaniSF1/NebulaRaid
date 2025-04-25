#include "BerserkerMovement.h"

BerserkerMovement::BerserkerMovement()
{
	player = GameWorld::instance().getPlayer();
	direction = {};
	targetPos = {};
	targetX = {};
	offsetX = {};
	offsetY = {};
}

void BerserkerMovement::update(Enemy* enemy)
{
	if (!player) player = GameWorld::instance().getPlayer();
	if (lastHealth <= 0) lastHealth = enemy->getHealth();
	if (mode != BerserkerMovementMode::Teleporting)
	{
		Vector2 newPosition = Vector2Add(enemy->getWorldPos(), Vector2Scale(direction, enemy->getSpeed() * GetFrameTime()));
		bool passedX = (direction.x > 0 && newPosition.x >= targetPos.x) || (direction.x < 0 && newPosition.x <= targetPos.x);
		bool passedY = (direction.y > 0 && newPosition.y >= targetPos.y) || (direction.y < 0 && newPosition.y <= targetPos.y);

		if (passedX && passedY)
		{
			enemy->setWorldPos(targetPos);
			newPos(enemy);
		}
		else enemy->setWorldPos(newPosition);
	}
	else
	{
		if (tpTime <= 0 || enemy->isOutOfBounds())
		{
			enemy->setWorldPos(targetPos);
			newPos(enemy);
			tpTime = tpDelay;
		}
	}
	
	if (currentCycle <= 0 || lastHealth - enemy->getHealth() >= damageThreshold)
	{
		changeCicle(enemy);
		currentCycle = cycleTime;
		lastHealth = enemy->getHealth();
	}

	currentCycle -= GetFrameTime();
	tpTime -= GetFrameTime();
	maxActiveSec -= GetFrameTime();
	if (maxActiveSec <= 0)
	{
		finished = true;
	}

#ifdef DEBUG_MODE
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
#endif
}

bool BerserkerMovement::isFinished() const
{
	return finished;
}

void BerserkerMovement::newPos(Enemy* enemy)
{
	switch (mode)
	{
	case BerserkerMovementMode::Random:
	case BerserkerMovementMode::Teleporting:
		targetPos = { movBounds.x + GetRandomValue(0, movBounds.width - enemy->getWidth() * enemy->getScale()), movBounds.y + GetRandomValue(0, movBounds.height - enemy->getWidth() * enemy->getScale()) };
		break;
	case BerserkerMovementMode::Stalking:
		offsetX = GetRandomValue(-radius, radius);
		offsetY = GetRandomValue(-radius, 0);

		Vector2 newPosition = Vector2Add(player->getWorldPos(), { offsetX, offsetY });
		targetPos.x = Clamp(newPosition.x, 0, GameConfig::instance().screenWidth - enemy->getWidth() * enemy->getScale());
		targetPos.y = Clamp(newPosition.y, 0, player->getWorldPos().y - offsetY);
		break;
	case BerserkerMovementMode::Lateral:
		targetX = GetRandomValue(10.f, GameConfig::instance().screenWidth - enemy->getWidth() * enemy->getScale());
		targetPos = { targetX, enemy->getWorldPos().y };
		break;
	default:
		break;
	}
	direction = Vector2Normalize(Vector2Subtract(targetPos, enemy->getWorldPos()));
}

void BerserkerMovement::changeCicle(Enemy* enemy)
{
	switch (mode)
	{
	case BerserkerMovementMode::Random:
		mode = BerserkerMovementMode::Lateral;
		break;
	case BerserkerMovementMode::Lateral:
		mode = BerserkerMovementMode::Teleporting;
		break;
	case BerserkerMovementMode::Teleporting: 
		mode = BerserkerMovementMode::Stalking;    
		break;
	case BerserkerMovementMode::Stalking:    
		mode = BerserkerMovementMode::Random;     
		break;

	}

	enemy->setSpeed(mode == BerserkerMovementMode::Stalking ? stalkingSpeed : speed);
}