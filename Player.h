#pragma once
#include "BaseCharacter.h"
#include "PlayerBullet.h"
#include <vector>


class Player : public BaseCharacter
{
public:
    Player();
    virtual void tick() override;
    virtual void shoot() override;
    void unloadTextures();

private:
    //Temporary vector
    std::vector<PlayerBullet> shots;
};

