#pragma once
#include "Bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	virtual void tick() override;
	virtual void checkCollision() override;

private:

};

