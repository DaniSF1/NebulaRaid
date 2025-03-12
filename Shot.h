#pragma once
#include "raylib.h"

class Shot
{
public:
	Shot(Texture2D texture, Vector2 pos, float speed, float xDirection, float yDirection, int type);
	void tick();
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }

private:
	Texture2D shotTexture{};
	Rectangle hitBox{};
	Vector2 shotPos{};
	float shotSpeed;
	float damage;
	int typeOfShot;

	//1.f positive X / -1.f negative X
	float shotXDirection;
	//1.f positive Y / -1.f negative Y
	float shotYDirection;

	bool isActive = false;
	float width;
	float height;

	// animation variables;
	float runningTime{};
	int frame{};
	int maxFrames{};
	float updateTime{};
	float scale{};
};