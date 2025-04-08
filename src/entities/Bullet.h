#pragma once
#include "raylib.h"
#include "../core/GameObject.h"

class Bullet : public GameObject
{
public:
	void tick() override;
	bool checkCollision(GameObject* obj);
	void initialize(Texture2D bulletTexture, Vector2 position, float bulletSpeed, int xRow, int yRow, int bulletDamage);
	int getDamage() { return damage; }
	void setDamage(int newDamage) { damage = newDamage; }

private:				
	int damage;
};