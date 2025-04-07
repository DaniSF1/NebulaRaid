#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "../entities/Bullet.h"
#include "Pool.h"

class BaseCharacter : public GameObject
{
public:
    BaseCharacter();
    virtual void tick();        
    virtual void undoMovement() = 0;
    virtual void shoot() = 0;
    void takeDamage();
    void bulletCollision(Bullet* bullet);
    Pool<Bullet>& getBulletPool() { return bulletPool; }

    ~BaseCharacter()
    {
        if (bulletTexture.id != 0)
        {
            UnloadTexture(bulletTexture);
        }
    }

protected:
    Pool<Bullet> bulletPool;
    Texture2D bulletTexture{};

private:
    float health{};
};

