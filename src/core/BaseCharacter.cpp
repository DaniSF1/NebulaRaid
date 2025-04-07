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

void BaseCharacter::takeDamage()
{
	setActive(false);
}

void BaseCharacter::bulletCollision(Bullet* bullet)
{
	bulletPool.releaseObject(bullet);
	takeDamage();
}
