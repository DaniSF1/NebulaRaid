#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Pool.h"

class BaseCharacter : public GameObject
{
public:
    BaseCharacter();
    virtual void tick();        
    virtual void undoMovement() = 0;
    virtual void shoot() = 0; 
    virtual void unloadTexture();

protected:
    Pool<Bullet> bulletPool;
    Texture2D bulletTexture{};

private:
    float health{};
};

