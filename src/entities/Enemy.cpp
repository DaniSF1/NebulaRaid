#include "Enemy.h"

Texture2D Enemy::sharedTexture = {};
Texture2D Enemy::sharedBulletTexture = {};

Enemy::Enemy()
{
	setActive(true);
	worldPos.x = GameConfig::instance().screenWidth / 2;
	worldPos.y = -100.f;
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
	scale = 2.5f;
	health = 20;
	movementBehavior = new EnterTopBehavior();
	attackBehavior = {};
}

void Enemy::tick()
{
	if (!getActive()) return;

	switch (state)
	{
	case EnemyState::Entering:
		movementBehavior->update(this);
		if (movementBehavior->isFinished())
		{
			state = EnemyState::Active;
			delete movementBehavior;
			//new movementBehavior
		}
		break;
	case EnemyState::Active:
		movementBehavior->update(this);
		attackBehavior->update(this);
		if (movementBehavior->isFinished())
		{
			state = EnemyState::Retreating;
		}
		break;
	case EnemyState::Retreating:

		break;
	default:
		break;
	}

	BaseCharacter::tick();

#ifdef DEBUG_MODE
	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
	DrawCircle(worldPos.x + (width * scale) / 2, worldPos.y + (height * scale) / 2, 5, RED);
#endif
}

void Enemy::undoMovement()
{
	
}

void Enemy::shoot()
{
	Bullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + width / 2, worldPos.y + height / 2 };
		bullet->initialize(bulletTexture, bulletPos, 1000.f, 4, 1, 20);
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
