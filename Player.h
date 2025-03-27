#pragma once
#include "BaseCharacter.h"
#include "PlayerBullet.h"
#include "Pool.h"

class Player : public BaseCharacter
{
public:
    Player();
    virtual void tick() override;
    virtual void shoot() override;

private:
    Pool<PlayerBullet> bulletPool;
};

