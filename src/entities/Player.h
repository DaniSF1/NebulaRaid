#pragma once
#include "../core/BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    Player();
    void tick() override;
    void draw(Color tint) override;
    void undoMovement() override;
    void shoot() override;
    void takeDamage(int damage) override;
    bool isInvincible() const { return activeInvincibility > 0.0f; }

    ~Player() override = default;

private:
    Vector2 lastFrameWorldPos{};
    float activeInvincibility = 0.0f;
    const float maxInvincibility = 0.75f;
};

