#include "Enemy.h"
#include "../behaviors/BerserkerMovement.h"

Texture2D Enemy::sharedTexture = {};
Texture2D Enemy::sharedBulletTexture = {};

Enemy::Enemy(size_t bulletCount) : BaseCharacter(bulletCount)
{
	setActive(true);

	xRows = 4;
	yRows = 1;
	
	runningTime = 0;
	frame = 0;
	updateTime = 0.15f;

	enterBehavior = nullptr;
	movementBehavior = nullptr;
	retreatBehavior = nullptr;
	attackBehavior = nullptr;
}

void Enemy::tick()
{
	if (getHealth() > 0)
	{
		switch (state)
		{
		case EnemyState::Entering:
			enterBehavior->update(this);

			if (enterBehavior->isFinished())
			{
				state = EnemyState::Active;
				delete enterBehavior;
				movementBehavior->newPos(this);
			}
			break;
		case EnemyState::Active:
			movementBehavior->update(this);
			attackBehavior->update(this);

			if (isOutOfBounds()) undoMovement();
			if (movementBehavior->isFinished())
			{
				state = EnemyState::Retreating;
				delete movementBehavior;
			}
			break;
		case EnemyState::Retreating:
			retreatBehavior->update(this);
			attackBehavior->update(this);

			if (retreatBehavior->isFinished())
			{
				setActive(false);
			}
			break;
		default:
			break;
		}

		if (isDamaged()) activeDamaged -= GetFrameTime();
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

void Enemy::draw(Color tint)
{
	if (getHealth() <= 0) return;

	if (!isDamaged())
	{
		GameObject::draw();
	}
	else 
	{
		bool visible = static_cast<int>(activeDamaged * 10) % 2 == 0;
		if (visible)
		{
			GameObject::draw(Fade(RED, 0.9f));
		}
	}
}

void Enemy::undoMovement()
{
	movementBehavior->newPos(this);
}

void Enemy::shoot(Vector2 dir)
{
	Bullet* bullet = bulletPool.getObject();
	if (bullet)
	{
		Vector2 bulletPos{ worldPos.x + width / 2, worldPos.y + height / 2 };
		bullet->initialize(bulletTexture, bulletPos, bulletSpeed, 4, 1, damage, Vector2Normalize(dir));
	}
}

void Enemy::takeDamage(int damage)
{
	activeDamaged = maxDamaged;
	BaseCharacter::takeDamage(damage);
}

BerserkerMovementMode Enemy::getCurrentMovementMode() const
{
	auto* berserkerMove = dynamic_cast<BerserkerMovement*>(movementBehavior);
	if (berserkerMove)
	{
		return berserkerMove->getMode();
	}

	return BerserkerMovementMode::Random;
}
