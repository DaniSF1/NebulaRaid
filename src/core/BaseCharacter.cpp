#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() : bulletPool(10)
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
				bullet->setActive(false);
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
