#include "BerserkerAttack.h"

BerserkerAttack::BerserkerAttack(float delay)
{
	bulletDelay = delay;
	actualDelay = 0.f;
	burstCooldown = 0.f;
	burstCount = 0;
	direction = { 0.f, 1.f };
	player = GameWorld::instance().getPlayer();
}

void BerserkerAttack::update(Enemy* enemy)
{
	if (!player) player = GameWorld::instance().getPlayer();
	if (!player->getActive()) return;
	if (!enemy->getActive()) return;

	actualDelay += GetFrameTime();
	burstCooldown -= GetFrameTime();

	BerserkerMovementMode mode = enemy->getCurrentMovementMode();

	switch (mode)
	{
	case BerserkerMovementMode::Random:
		if (burstCooldown > 0.f) break;
		
		if (burstCount < 10 && actualDelay >= 0.05f)
		{
			direction = { 0.f, 1.f };
			enemy->shoot({direction});
			actualDelay = 0.f;
			burstCount++;
		}
		else if (burstCount >= 10 && burstCooldown <= 0.f)
		{
			burstCount = 0;
			burstCooldown = 1.f;
		}
		break;

	case BerserkerMovementMode::Teleporting:
		if (burstCooldown > 0.f) break;

		if (burstCount < 5 && actualDelay >= 0.1f)
		{
			precisionShot(enemy);
			actualDelay = 0.f;
			burstCount++;
		}
		else if (burstCount >= 5 && burstCooldown <= 0.f)
		{
			burstCount = 0;
			burstCooldown = 1.f;
		}

		break;
	case BerserkerMovementMode::Stalking:
		if (actualDelay >= bulletDelay)
		{
			precisionShot(enemy);
			actualDelay = 0.f;
		}

		break;
	case BerserkerMovementMode::Lateral:
		if (burstCooldown <= 0.f)
		{
			circularShot(enemy, 12);
			burstCooldown = 1.f;
		}

		break;
	default:
		break;
	}
}

void BerserkerAttack::precisionShot(Enemy* enemy)
{
	Vector2 enemyCenter = { enemy->getWorldPos().x + enemy->getWidth() * enemy->getScale() / 2, enemy->getWorldPos().y + enemy->getHeight() * enemy->getScale() / 2 };
	Vector2 playerCenter = { player->getWorldPos().x + player->getWidth() * player->getScale() / 2, player->getWorldPos().y + player->getHeight() * player->getScale() / 2 };

	direction = Vector2Normalize(Vector2Subtract(playerCenter, enemyCenter));
	enemy->shoot(direction);
}

void BerserkerAttack::circularShot(Enemy* enemy, int bullets)
{
	Vector2 center = { enemy->getWorldPos().x + enemy->getWidth() * enemy->getScale() / 2, enemy->getWorldPos().y + enemy->getHeight() * enemy->getScale() / 2 };

	float step = 360.f / bullets;
	for (int i = 0; i < bullets; ++i)
	{
		float angle = DEG2RAD * (step * i);
		direction = { cosf(angle), sinf(angle) };
		enemy->shoot(direction);
	}
}
