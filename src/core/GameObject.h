#pragma once
#include "raylib.h"
#include "../utils/GameConfig.h"
#define DEBUG_MODE

class GameObject
{
public: 
	virtual void tick();
	virtual void draw(Color tint = WHITE);
	bool isOutOfBounds();
	Rectangle getHitbox();
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }
	Vector2 getWorldPos() { return worldPos; }
	void setWorldPos(Vector2 newPos) { worldPos = newPos; }
	float getSpeed() { return speed; }

	virtual ~GameObject() = default;

protected:
	Texture2D texture{};            
	Vector2 worldPos{};
	Rectangle hitbox{};

	float speed{};                  
	float width{};
	float height{};
	float scale{};

	int xRows;
	int yRows;

	// animation variables          
	float runningTime{};
	int frame{};
	float updateTime{};

private:
	bool isActive;
};