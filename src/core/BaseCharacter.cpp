#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(size_t bulletPoolSize) : bulletPool(bulletPoolSize)
{
}

void BaseCharacter::tick()
{
	for (Bullet* bullet : bulletPool.getAllActiveObjects())
	{
		if (bullet)
		{
			bullet->tick();

			if (bullet->isOutOfBounds())
			{
				bullet->resetBullet();
				bulletPool.releaseObject(bullet);
			}
		}
	}

	GameObject::tick();
}

void BaseCharacter::takeDamage(int damage)
{
	if (health > 0)
	{
		health -= damage;
	}
	if (health <= 0)
	{
		setActive(false);
	}
}

void BaseCharacter::bulletCollision(Bullet* bullet)
{
	takeDamage(bullet->getDamage());
	bullet->setActive(false);
}

Rectangle BaseCharacter::getHitbox()
{
	if (health <= 0) return Rectangle{-1000, -1000, 1, 1};
	return GameObject::getHitbox();
}
