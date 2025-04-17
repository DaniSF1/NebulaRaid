#include "BasicAttackBehavior.h"


void BasicAttackBehavior::update(Enemy* enemy)
{
	if (readyToShoot)
	{
		enemy->shoot();
		readyToShoot = false;
	}

	bulletDelay += GetFrameTime();
	if (bulletDelay >= 0.5f)
	{
		bulletDelay = 0.f;
		readyToShoot = true;
	}
}
