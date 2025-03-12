#pragma once
#include "Bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(Texture2D texture, Vector2 pos, float speed, float xDirection, float yDirection, int type);
	virtual void tick() override;
	virtual void checkCollision() override;

private:

};

