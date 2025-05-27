#include "TurretAttack.h"

TurretAttack::TurretAttack(float delay)
{
	bulletDelay = delay;
	actualDelay = 0;
}

void TurretAttack::update(Enemy* enemy)
{
	if (!enemy->getActive()) return;
	actualDelay += GetFrameTime();
	if (actualDelay < bulletDelay) return;

	Vector2 center = { enemy->getWorldPos().x + enemy->getWidth() * enemy->getScale() / 2, enemy->getWorldPos().y + enemy->getHeight() * enemy->getScale() / 2 };
	float step = 360.f / numberOfBullets;
	float angle = DEG2RAD * (step * currentBullet);
	Vector2 direction = Vector2Normalize({ cosf(angle), sinf(angle) });
	enemy->shoot(direction);

	currentBullet++;
	if (currentBullet >= numberOfBullets) currentBullet = 0;
	if (actualDelay >= bulletDelay) actualDelay = 0.f;
}
