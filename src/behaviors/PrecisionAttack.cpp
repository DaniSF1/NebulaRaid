#include "PrecisionAttack.h"

void PrecisionAttack::update(Enemy* enemy)
{
	bulletDelay += GetFrameTime();
	if (bulletDelay < 1.f) return;

	player = GameWorld::instance().getPlayer();
	if (!player || !player->getActive()) return;

	Vector2 enemyCenter = { enemy->getWorldPos().x + enemy->getWidth() * enemy->getScale() / 2, enemy->getWorldPos().y + enemy->getHeight() * enemy->getScale() / 2 };
	Vector2 playerCenter = { player->getWorldPos().x + player->getWidth() * player->getScale() / 2, player->getWorldPos().y + player->getHealth() * player->getScale() / 2 };
	
	Vector2 direction = Vector2Normalize(Vector2Subtract(playerCenter, enemyCenter));

	enemy->shoot(direction);

	if (bulletDelay >= 0.5f) bulletDelay = 0.f;
}
