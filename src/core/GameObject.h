#pragma once
#include "raylib.h"
#include "../utils/GameConfig.h"
//#define DEBUG_MODE

class GameObject
{
public: 
	virtual void tick();
	virtual void draw(Color tint = WHITE);
	bool isOutOfBounds();
	Rectangle getHitbox();
	void setHitbox(Rectangle r) { hitbox = r; }
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }
	Vector2 getWorldPos() { return worldPos; }
	void setWorldPos(Vector2 newPos) { worldPos = newPos; }
	float getSpeed() { return speed; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	float getScale() { return scale; }
	void setScale(float newScale) { scale = newScale; }
	Texture2D getTexture() { return texture; }
	void setTexture(Texture2D tex) { texture = tex; }
	float getWidth() { return width; }
	void setWidth(float w) { width = w; }
	float getHeight() { return height; }
	void setHeight(float h) { height = h; }
	int getXRows() { return xRows; }
	void setXRows(int x) { xRows = x; }
	int getYRows() { return yRows; }
	void setYRows(int y) { yRows = y; }


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