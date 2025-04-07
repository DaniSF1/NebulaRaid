#pragma once
#include "raylib.h"
#define DEBUG_MODE

class GameObject
{
public: 
	virtual void tick();
	void draw();
	bool isOutOfBounds();
	Rectangle getHitbox();
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }

	virtual ~GameObject() 
	{
		if (texture.id != 0) 
		{
			UnloadTexture(texture);
		}
	}

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