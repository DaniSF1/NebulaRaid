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
	void initialize(Texture2D texture, Vector2 position, float speed, float xDir, float yDir, int type, int maxFr);

protected:
	Texture2D bulletTexture{};
	Rectangle hitBox{};
	Vector2 bulletPos{};
	float bulletSpeed;
	float damage;
	int bulletType;

	//1.f positive X / -1.f negative X
	float bulletXDirection;
	//1.f positive Y / -1.f negative Y
	float bulletYDirection;

	bool isActive;
	float width;
	float height;

	// animation variables;
	float runningTime{};
	int frame{};
	int maxFrames{};
	float updateTime{};
	float scale{};
};

