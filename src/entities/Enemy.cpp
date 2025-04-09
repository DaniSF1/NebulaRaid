#include "Enemy.h"

Texture2D Enemy::sharedTexture = {};
Texture2D Enemy::sharedBulletTexture = {};

Enemy::Enemy()
{
	setActive(true);
	worldPos.x = GameConfig::instance().screenWidth / 2;
	worldPos.y = GameConfig::instance().screenHeight / 4;
	speed = 300.f;

	texture = sharedTexture;
	bulletTexture = sharedBulletTexture;
	xRows = 4;
	yRows = 1;
	width = texture.width / xRows;
	height = texture.height / yRows;
	hitbox = Rectangle{ worldPos.x, worldPos.y, width, height };

	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	scale = 2;
	readyToShoot = true;
	bulletDelay = 0.f;
	targetPos = {0.f, 0.f};
	movBounds = Rectangle{ 0.0f, 0.0f, 720.f, 500.f };
	health = 20;
	newPos();
}

void Enemy::tick()
{
	if (!getActive()) return;

	if (readyToShoot)
	{
		shoot();
		readyToShoot = false;
	}

	bulletDelay += GetFrameTime();
	if (bulletDelay >= 0.5f)
	{
		readyToShoot = true;
		bulletDelay = 0;
	}

	worldPos = Vector2Add(worldPos, Vector2Scale(direction, speed * GetFrameTime()));
	if (Vector2DistanceSqr(worldPos, targetPos) < 10.f || isOutOfBounds()) undoMovement();

	BaseCharacter::tick();

#ifdef DEBUG_MODE
	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
	DrawCircle(worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2, 5, RED);
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
#endif
}

void Enemy::undoMovement()
{
	newPos();
}

void Enemy::shoot()
{
	Bullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + width / 2, worldPos.y + height / 2 };
		bullet->initialize(bulletTexture, bulletPos, 600.f, 4, 1, 20);
	}
}

void Enemy::LoadSharedTexture()
{
	sharedTexture = LoadTexture("assets/ships/Enemies/Enemies_T1.png");
	sharedBulletTexture = LoadTexture("assets/ships/Enemies/Enemies_T1_bullet.png");
}

void Enemy::UnloadSharedTexture()
{
	UnloadTexture(sharedTexture);
	UnloadTexture(sharedBulletTexture);
}

void Enemy::newPos()
{
	targetPos = { movBounds.x + GetRandomValue(0, movBounds.width), movBounds.y + GetRandomValue(0, movBounds.height)};
	direction = Vector2Normalize(Vector2Subtract(targetPos, worldPos));
}
