#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	isActive = false;
	scale = 4.f;
	updateTime = 0.3f;
	rotation = 0.2f;
}

void EnemyBullet::tick()
{
	if (!isActive) return;

	//bulletPos.x -= bulletSpeed;
	bulletPos.y += bulletSpeed * bulletYDirection * GetFrameTime();

	Bullet::tick();

	DrawRectangleLines(
		hitBox.x,
		hitBox.y,
		hitBox.width,
		hitBox.height,
		RED);
}

void EnemyBullet::checkCollision()
{
}