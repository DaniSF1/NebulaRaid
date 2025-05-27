#include "PrecisionAttack.h"

PrecisionAttack::PrecisionAttack(float delay)
{
	bulletDelay = delay;
	actualDelay = 0;
	player = nullptr;
}

void PrecisionAttack::update(Enemy* enemy)
{
	if (!enemy->getActive()) return;
	actualDelay += GetFrameTime();
	if (!player) player = GameWorld::instance().getPlayer();
	if (actualDelay < bulletDelay || !player || !player->getActive()) return;

	Vector2 enemyCenter = { enemy->getWorldPos().x + enemy->getWidth() * enemy->getScale() / 2, enemy->getWorldPos().y + enemy->getHeight() * enemy->getScale() / 2 };
	Vector2 playerCenter = { player->getWorldPos().x + player->getWidth() * player->getScale() / 2, player->getWorldPos().y + player->getHealth() * player->getScale() / 2 };
	
	Vector2 direction = Vector2Normalize(Vector2Subtract(playerCenter, enemyCenter));

	enemy->shoot(direction);

	if (actualDelay >= bulletDelay) actualDelay = 0.f;
}
