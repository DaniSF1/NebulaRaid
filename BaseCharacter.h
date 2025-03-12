#pragma once
#include "raylib.h"

class BaseCharacter
{
public:
    virtual void tick();
    void undoMovement();
    virtual void shoot() = 0;
    Rectangle getCollisionRec();
    bool getAlive() { return isAlive; }
    void setAlive(bool alive) { isAlive = alive; }

protected:
	Texture2D texture{};
    Texture2D shotTexture{};
	Vector2 worldPos{};
	Vector2 lastFrameWorldPos{};

    // 1 right / -1 left
    float rightLeft = 1.f;

    // animation variables;
    float runningTime{};
    int frame{};
    int maxFrames{};
    float updateTime{};

    float speed{};
    float width{};
    float height{};
    float scale{};
    Vector2 velocity{};
    float health{};

private:
    bool isAlive;
};

