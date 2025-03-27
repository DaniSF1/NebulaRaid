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
		if (frame > xRows)
			frame = 0;
	}

	hitBox.x = bulletPos.x - width / 2;
	hitBox.y = bulletPos.y - height / 2;

	// Draw the bullet
	Rectangle source{ frame * width, bulletType * height, width, height };
	Rectangle dest{ bulletPos.x, bulletPos.y, scale * width, scale * height };
	Vector2 origin{ (scale * width) / 2, (scale * height) / 2 };
	DrawTexturePro(bulletTexture, source, dest, origin, 0.f, WHITE);
}

bool Bullet::isOutOfBounds()
{
	return 
		bulletPos.x < 0 || 
		bulletPos.y < 0 || 
		bulletPos.x + width / 2 > 720 || 
		bulletPos.y + height / 2 > 1280;
}

void Bullet::initialize(Texture2D texture, Vector2 position, float speed, float yDir, int type, int xRow, int yRow)
{
	isActive = true;

	bulletTexture = texture;
	bulletPos = position;
	bulletSpeed = speed + 50.f * type;
	bulletYDirection = yDir;
	bulletType = type;
	xRows = xRow;
	yRows = yRow;

	width = bulletTexture.width / xRows;
	height = bulletTexture.height / yRows;

	hitBox = Rectangle{
		bulletPos.x - width / 2,
		bulletPos.y - height / 2,
		width,
		height
	};

	damage = 40 + 20 * bulletType;

	runningTime = 0;
	frame = 0;
}