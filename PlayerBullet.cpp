#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	isActive = false;
	scale = 4.f;
	updateTime = 0.15f;
}

void PlayerBullet::tick()
{
	if (!isActive) return;

	bulletPos.y += bulletSpeed * bulletYDirection * GetFrameTime();

	Bullet::tick();

	DrawRectangleLines(
		hitBox.x,
		hitBox.y,
		hitBox.width,
		hitBox.height,
		RED);
}

void PlayerBullet::checkCollision()
{

}