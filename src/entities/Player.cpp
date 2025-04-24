#include "Player.h"

Player::Player() : BaseCharacter(10)
{
	setActive(true);
	worldPos.x = GameConfig::instance().screenWidth / 2;
	worldPos.y = GameConfig::instance().screenHeight / 2;
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
	health = 100;
}

void Player::tick()
{
	if (!getActive()) return;

	if (IsKeyDown(KEY_W)) worldPos.y -= speed * GetFrameTime();
	if (IsKeyDown(KEY_S)) worldPos.y += speed * GetFrameTime();
	if (IsKeyDown(KEY_A)) worldPos.x -= speed * GetFrameTime();
	if (IsKeyDown(KEY_D)) worldPos.x += speed * GetFrameTime();
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) shoot(Vector2({0.f, -1.f}));

	if (isOutOfBounds())
	{
		undoMovement();
	}

	lastFrameWorldPos = worldPos;

	std::string remainingHealth = "Health: " + std::to_string(health);
	DrawText(remainingHealth.c_str(), 10, 10, 20, WHITE);

	if (isInvincible()) activeInvincibility -= GetFrameTime();

	BaseCharacter::tick();

#ifdef DEBUG_MODE
	std::string remainingBulletsText = "Remaining Bullets: " + std::to_string(bulletPool.getAvailableObjects().size());
	DrawText(remainingBulletsText.c_str(), 10, 30, 20, WHITE);

	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
	DrawCircle(worldPos.x + width, worldPos.y + height, 5, RED);
#endif
}

void Player::draw(Color tint)
{
	if (!isInvincible())
	{
		GameObject::draw();
	}
	else
	{
		bool visible = static_cast<int>(activeInvincibility * 10) % 2 == 0;
		if (visible)
		{
			GameObject::draw(Fade(WHITE, 0.4f));
		}
	}
}

void Player::undoMovement()
{
	worldPos = lastFrameWorldPos;
}

void Player::shoot(Vector2 dir)
{
	Bullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + width / 2, worldPos.y + height / 2};
		bullet->initialize(bulletTexture, bulletPos, 800.f, 4, 1, 20, Vector2Normalize(dir));
	}
}

void Player::takeDamage(int damage)
{
	if (isInvincible()) return;

	activeInvincibility = maxInvincibility;
	BaseCharacter::takeDamage(damage);

}
