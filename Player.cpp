#include "Player.h"
#include <string>

Player::Player()
{
	setActive(true);
	worldPos.x = 720 / 2;
	worldPos.y = 1280 / 2;
	speed = 700.f;

	texture = LoadTexture("assets/ships/Player/Ship-Nebula - Sprite Sheet.png");
	bulletTexture = LoadTexture("assets/ships/Player/Nebula Shot Levels - Sprite Sheet 32x32.png");
	xRows = 4;
	yRows = 1;
	width = texture.width / xRows;
	height = texture.height / yRows;

	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	scale = 2;
	hitbox = Rectangle{worldPos.x, worldPos.y, width, height};
}

void Player::tick()
{
	if (!getActive()) return;

	if (IsKeyDown(KEY_W)) worldPos.y -= speed * GetFrameTime();
	if (IsKeyDown(KEY_S)) worldPos.y += speed * GetFrameTime();
	if (IsKeyDown(KEY_A)) worldPos.x -= speed * GetFrameTime();
	if (IsKeyDown(KEY_D)) worldPos.x += speed * GetFrameTime();
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) shoot();

	if (isOutOfBounds())
	{
		undoMovement();
	}

	lastFrameWorldPos = worldPos;

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
	DrawCircle(worldPos.x + width, worldPos.y + height, 5, RED);
}

void Player::undoMovement()
{
	worldPos = lastFrameWorldPos;
}

void Player::shoot()
{
	Bullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + width / 2, worldPos.y + height / 2};
		bullet->initialize(bulletTexture, bulletPos, -800.f, 4, 3);
	}
}