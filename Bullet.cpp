#include "Bullet.h"

void Bullet::tick()
{
	if (!getActive()) return;

	worldPos.y += speed * GetFrameTime();
	GameObject::tick();

#ifdef DEBUG_MODE
	DrawRectangleLines(
		getHitbox().x,
		getHitbox().y,
		getHitbox().width,
		getHitbox().height,
		RED);
#endif
}

bool Bullet::checkCollision(GameObject* obj)
{
	return CheckCollisionRecs(getHitbox(), obj->getHitbox());
}

void Bullet::handleCollision()
{
	setActive(false);
}

void Bullet::initialize(Texture2D bulletTexture, Vector2 position, float bulletSpeed, int xRow, int yRow)
{
	setActive(true);

	texture = bulletTexture;
	worldPos = position;
	speed = bulletSpeed;
	xRows = xRow;
	yRows = yRow;
	width = texture.width / xRows;
	height = texture.height / yRows;
	scale = 1;

	hitbox = Rectangle{ worldPos.x, worldPos.y, width, height };
	runningTime = 0;
	frame = 0;

	damage = 40;
}