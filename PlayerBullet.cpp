#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Texture2D texture, Vector2 pos, float speed, float xDirection, float yDirection, int type)
{
	isActive = true;
	bulletTexture = texture;
	bulletPos = pos;
	bulletSpeed = speed;
	bulletXDirection = xDirection;
	bulletYDirection = yDirection;
	maxFrames = 4;
	width = texture.width / maxFrames;
	height = texture.height / 3;
	scale = 4.f;
	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	bulletType = type;
	damage = 40 + 20 * type;

	hitBox = Rectangle{
		bulletPos.x - width / 2,
		bulletPos.y - height / 2,
		width,
		height
	};
}

void PlayerBullet::tick()
{
	if (!isActive) return;
	Bullet::tick();

	DrawRectangleLines(
		hitBox.x,
		hitBox.y,
		hitBox.width,
		hitBox.height,
		RED);
	//DrawCircle(bulletPos.x + (width * scale) / 2, bulletPos.y + (height * scale) / 2, 5, RED);
}

void PlayerBullet::checkCollision()
{

}
