#pragma once
#include "raylib.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	void tick() override;
	void checkCollision();
	void initialize(Texture2D bulletTexture, Vector2 position, float bulletSpeed, int xRow, int yRow);

protected:				
	float damage;
};