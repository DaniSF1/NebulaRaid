#pragma once
#include "BaseCharacter.h"
#include "Shot.h"
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
    std::vector<Shot> shots;
};

