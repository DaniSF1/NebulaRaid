#include "Enemy.h"

Enemy::Enemy() : bulletPool(10)
{
	worldPos.x = 720 / 2;
	worldPos.y = 1280 / 4;
	speed = 300.f;

	texture = LoadTexture("assets/ships/Enemies/Enemies_T1.png");
	bulletTexture = LoadTexture("assets/ships/Enemies/Enemies_T1_bullet.png");
	maxFrames = 4;
	width = texture.width / maxFrames;
	height = texture.height;

	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;
	scale = 2;
	readyToShoot = true;
	bulletDelay = 0.f;
	targetPos = {0.f, 0.f};
	movBounds = Rectangle{0.0f, 0.0f, 720.f, 500.f};
	newPos();
}

void Enemy::tick()
{
	BaseCharacter::tick();

	/*if (readyToShoot)
	{
		shoot();
		readyToShoot = false;
	}*/

	for (EnemyBullet* bullet : bulletPool.getAllActiveObjects())
	{
		if (bullet)
		{
			bullet->tick();

			if (bullet->isOutOfBounds())
			{
				bullet->setActive(false);
				bulletPool.releaseObject(bullet);
			}
		}
	}

	//bulletDelay += GetFrameTime();
	//if (bulletDelay >= 0.5f)
	//{
	//	readyToShoot = true;
	//	bulletDelay = 0;
	//}

	/*worldPos = Vector2Add(worldPos, Vector2Scale(direction, speed * GetFrameTime()));
	if (Vector2DistanceSqr(worldPos, targetPos) < 10.f) newPos();*/

	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
	DrawCircle(worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2, 5, RED);
	DrawCircle(targetPos.x, targetPos.y, 5, YELLOW);
}

void Enemy::shoot()
{
	EnemyBullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2 };
		bullet->initialize(bulletTexture, bulletPos, 600.f, 1.0f, 0, 4, 1);
	}
}

void Enemy::newPos()
{
	targetPos = { 
		movBounds.x + GetRandomValue(0, movBounds.width - width),
		movBounds.y + GetRandomValue(0, movBounds.height)
	};

	direction = Vector2Normalize(Vector2Subtract(targetPos, worldPos));
}
