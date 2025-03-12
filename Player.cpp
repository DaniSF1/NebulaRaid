#include "Player.h"

Player::Player()
{
	worldPos.x = 720 / 2;
	worldPos.y = 1280 / 2;
	speed = 10.f;

	texture = LoadTexture("assets/ships/Ship-Nebula - Sprite Sheet.png");
	shotTexture = LoadTexture("assets/ships/Nebula Shot Levels - Sprite Sheet 32x32.png");
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

	if (IsKeyDown(KEY_W)) worldPos.y -= speed;
	if (IsKeyDown(KEY_S)) worldPos.y += speed;
	if (IsKeyDown(KEY_A)) worldPos.x -= speed;
	if (IsKeyDown(KEY_D)) worldPos.x += speed;
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) shoot();

	for (Shot& shot : shots)
	{
		shot.tick();
	}

	BaseCharacter::tick();

	DrawRectangleLines(
		getCollisionRec().x,
		getCollisionRec().y,
		getCollisionRec().width,
		getCollisionRec().height,
		RED);
	DrawCircle(worldPos.x + width, worldPos.y + height, 5, RED);
}

void Player::shoot()
{
	Vector2 shotPos{worldPos.x, worldPos.y};
	Shot newShot(shotTexture, shotPos, 20.f, 0.0f, -1.0f, 0);
	shots.push_back(newShot);
}

void Player::unloadTextures()
{
	UnloadTexture(texture);
	UnloadTexture(shotTexture);
}
