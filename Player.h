#pragma once
#include "BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    Player();
    virtual void tick() override;
    virtual void undoMovement() override;
    virtual void shoot() override;

private:
    Vector2 lastFrameWorldPos{};
};

