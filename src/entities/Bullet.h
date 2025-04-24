#pragma once
#include "raylib.h"
#include "../core/GameObject.h"
#include "raymath.h"

class Bullet : public GameObject
{
public:
	void tick() override;
	bool checkCollision(GameObject* obj);
	void initialize(Texture2D bulletTexture, Vector2 position, float bulletSpeed, int xRow, int yRow, int bulletDamage, Vector2 dir);
	int getDamage() { return damage; }
	void setDamage(int newDamage) { damage = newDamage; }
	void resetBullet();
	Vector2 getDirection() { return direction; }

private:				
	int damage;
	Vector2 direction;
};