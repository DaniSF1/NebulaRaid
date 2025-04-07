#pragma once
#include "../core/BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    Player();
    virtual void tick() override;
    virtual void undoMovement() override;
    virtual void shoot() override;

    ~Player() override = default;

private:
    Vector2 lastFrameWorldPos{};
};

