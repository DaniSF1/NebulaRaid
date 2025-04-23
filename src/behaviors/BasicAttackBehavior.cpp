#include "BasicAttackBehavior.h"


void BasicAttackBehavior::update(Enemy* enemy)
{
	bulletDelay += GetFrameTime();
	if (bulletDelay < 0.5f) return;

	enemy->shoot(Vector2({ 0.f, 1.f }));

	if (bulletDelay >= 0.5f) bulletDelay = 0.f;
}
