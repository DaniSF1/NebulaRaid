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
	this->texture = bulletTexture;
	this->worldPos = position;
	this->speed = bulletSpeed;
	this->xRows = xRow;
	this->yRows = yRow;
	this->width = texture.width / xRows;
	this->height = texture.height / yRows;
	this->scale = 1;
	this->direction = Vector2Normalize(dir);

	this->hitbox = Rectangle{ worldPos.x, worldPos.y, width, height };
	this->runningTime = 0;
	this->frame = 0;

	this->damage = bulletDamage;
}

void Bullet::resetBullet()
{
	setActive(false);
	this->direction = { 0, 0 };
	this->damage = 0;
	this->speed = 0;
}
