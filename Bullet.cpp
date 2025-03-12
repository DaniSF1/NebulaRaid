#include "Bullet.h"

void Bullet::tick()
{
	if (!isActive) return;

	// update animation frame
	runningTime += GetFrameTime();
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0.f;
		if (frame > maxFrames)
			frame = 0;
	}

	bulletPos.x += bulletSpeed * bulletXDirection;
	bulletPos.y += bulletSpeed * bulletYDirection;
	hitBox.x = bulletPos.x - width / 2;
	hitBox.y = bulletPos.y - height / 2;

	// Draw the bullet
	Rectangle source{ frame * width, bulletType * height, width, height };
	Rectangle dest{ bulletPos.x, bulletPos.y, scale * width, scale * height };
	Vector2 origin{ (scale * width) / 2, (scale * height) / 2 };
	DrawTexturePro(bulletTexture, source, dest, origin, 0.f, WHITE);

	if (bulletPos.x < 0 ||
		bulletPos.y < 0 ||
		bulletPos.x + width / 2 > 720 ||
		bulletPos.y + height / 2 > 1280)
	{
		setActive(false);
	}
}
