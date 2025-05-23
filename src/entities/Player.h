#pragma once
#include "../core/BaseCharacter.h"
#include "../utils/GameConfig.h"
#include "../utils/AudioManager.h"
#include <string>

class Player : public BaseCharacter
{
public:
    Player();
    void tick() override;
    void draw(Color tint) override;
    void undoMovement() override;
    void shoot(Vector2 dir) override;
    void takeDamage(int damage) override;
    bool isInvincible() const { return activeInvincibility > 0.0f; }
    int getScore() { return score; }
    void setScore(int newScore) { score = newScore; }

    ~Player() override
    {
        AudioManager::instance().playSound("death");
        if (texture.id != 0) UnloadTexture(texture);
        if (bulletTexture.id != 0) UnloadTexture(bulletTexture);
    }

private:
    Vector2 lastFrameWorldPos{};
    float activeInvincibility = 0.0f;
    const float maxInvincibility = 0.75f;
    float precisionSpeed = 0.f;
    float baseSpeed = 0.f;
    float shootCooldown = 0.f;
    const float shootDelay = 0.15f;
    
    int score = 10000;
    float scorePenalty = 10.f;
    float penaltyAccumulator = 0.0f;

    void drawInterface();
    void subtractScore();
};

