#include "Player.h"
#include <string>

Player::Player() : bulletPool(10)
{
	worldPos.x = 720 / 2;
	worldPos.y = 1280 / 2;
	speed = 700.f;

	texture = LoadTexture("assets/ships/Player/Ship-Nebula - Sprite Sheet.png");
	bulletTexture = LoadTexture("assets/ships/Player/Nebula Shot Levels - Sprite Sheet 32x32.png");
	maxFrames = 4;
	width = texture.width / maxFrames;
	height = texture.height;

	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	scale = 2;
}

void Player::tick()
{
	if (getAlive()) return;

	if (IsKeyDown(KEY_W)) worldPos.y -= speed * GetFrameTime();
	if (IsKeyDown(KEY_S)) worldPos.y += speed * GetFrameTime();
	if (IsKeyDown(KEY_A)) worldPos.x -= speed * GetFrameTime();
	if (IsKeyDown(KEY_D)) worldPos.x += speed * GetFrameTime();
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) shoot();

	for (PlayerBullet* bullet : bulletPool.getAllActiveObjects())
	{
 		if (bullet)
		{
			bullet->tick();

			if(bullet->isOutOfBounds())
			{
				bullet->setActive(false);
				bulletPool.releaseObject(bullet);
			}
		}
	}

	if (worldPos.x < 0 ||
		worldPos.y < 0 ||
		worldPos.x + 2 * width >= 720 ||
		worldPos.y + 2 * height >= 1280)
	{
		undoMovement();
	}

	BaseCharacter::tick();

	//Debug
	std::string remainingBulletsText = "Remaining Bullets: " + std::to_string(bulletPool.getAvailableObjects().size());
	DrawText(remainingBulletsText.c_str(), 10, 10, 20, WHITE);

	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
	DrawCircle(worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2, 5, RED);
}

void Player::shoot()
{
	PlayerBullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2 };
		bullet->initialize(bulletTexture, bulletPos, 800.f, -1.0f, 0, 4, 3);
	}
}