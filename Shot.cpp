#include "Shot.h"

Shot::Shot(Texture2D texture, Vector2 pos, float speed, float xDirection, float yDirection, int type)
{
	isActive = true;
	shotTexture = texture;
	shotPos = pos;
	shotSpeed = speed;
	shotXDirection = xDirection;
	shotYDirection = yDirection;
	maxFrames = 4;
	width = texture.width / maxFrames;
	height = texture.height / 5;
	scale = 4.f;
	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	typeOfShot = type;
	damage = 40 + 20 * type;

	hitBox = Rectangle{
		shotPos.x,
		shotPos.y,
		width,
		height
	};
}

void Shot::tick()
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

	shotPos.x += shotSpeed * shotXDirection;
	shotPos.y += shotSpeed * shotYDirection;

	// Draw the character
	Rectangle source{ frame * width, typeOfShot * height, width, height };
	Rectangle dest{ shotPos.x - width, shotPos.y - height, scale * width, scale * height };
	DrawTexturePro(shotTexture, source, dest, Vector2{}, 0.f, WHITE);

	if (shotPos.x < 0 ||
		shotPos.y < 0 ||
		shotPos.x + width / 2 > 720 ||
		shotPos.y + height / 2 > 1280)
	{
		setActive(false);
	}
}
