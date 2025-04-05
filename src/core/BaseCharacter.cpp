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

void BaseCharacter::unloadTexture()
{
	UnloadTexture(bulletTexture);
	GameObject::unloadTexture();
}

void BaseCharacter::takeDamage()
{
	setActive(false);
}
