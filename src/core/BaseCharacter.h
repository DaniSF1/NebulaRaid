#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "../entities/Bullet.h"
#include "Pool.h"

class BaseCharacter : public GameObject
{
public:
    BaseCharacter(size_t bulletPoolSize);
    virtual void tick();        
    virtual void undoMovement() = 0;
    virtual void shoot(Vector2 dir) = 0;
    virtual void takeDamage(int damage);
    void bulletCollision(Bullet* bullet);
    Rectangle getHitbox() override;
    Pool<Bullet>& getBulletPool() { return bulletPool; }

    int getHealth() { return health; }
    void setHealth(int newHealth) { health = newHealth; }
    void setBulletTexture(Texture2D bulletTex) { bulletTexture = bulletTex; }

    virtual ~BaseCharacter() = default;

protected:
    Pool<Bullet> bulletPool;
    Texture2D bulletTexture{};
    int health{};

};

