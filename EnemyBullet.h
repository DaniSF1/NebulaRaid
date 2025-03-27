#pragma once
#include "Bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	virtual void tick() override;
	virtual void checkCollision() override;

private:
	float rotation;
};

