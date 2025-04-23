#include "Bullet.h"

void Bullet::tick()
{
	if (!getActive()) return;

	worldPos = Vector2Add(worldPos, Vector2Scale(direction, speed * GetFrameTime()));
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

void Bullet::initialize(Texture2D bulletTexture, Vector2 position, float bulletSpeed, int xRow, int yRow, int bulletDamage, Vector2 dir)
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
	direction = dir;

	hitbox = Rectangle{ worldPos.x, worldPos.y, width, height };
	runningTime = 0;
	frame = 0;

	damage = bulletDamage;
}