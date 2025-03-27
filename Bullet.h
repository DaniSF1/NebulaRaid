#pragma once
#include "raylib.h"

class Bullet
{
public:
	virtual void tick();
	virtual void checkCollision() = 0;
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }
	bool isOutOfBounds();
	void initialize(Texture2D texture, Vector2 position, float speed, float yDir, int type, int xRow, int yRow);

protected:
	Texture2D bulletTexture{};
	Rectangle hitBox{};
	Vector2 bulletPos{};
	float bulletSpeed;
	float damage;
	int bulletType;

	//1.f positive Y / -1.f negative Y
	float bulletYDirection;

	bool isActive;
	float width;
	float height;

	// animation variables;
	float runningTime{};
	int frame{};
	float updateTime{};
	float scale{};
	int xRows;
	int yRows;
};