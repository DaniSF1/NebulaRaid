#include "BasicAttackBehavior.h"


BasicAttackBehavior::BasicAttackBehavior(float delay)
{
	bulletDelay = delay;
	actualDelay = 0;
}

void BasicAttackBehavior::update(Enemy* enemy)
{
	if (!enemy->getActive()) return;
	actualDelay += GetFrameTime();
	if (actualDelay < bulletDelay) return;

	enemy->shoot(Vector2({ 0.f, 1.f }));

	if (actualDelay >= bulletDelay) actualDelay = 0.f;
}
