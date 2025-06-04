#include "GameObject.h"
#include "../utils/GameConfig.h"

void GameObject::tick()
{
    if (!getActive()) return;
    draw();

    hitbox.x = worldPos.x;
    hitbox.y = worldPos.y;
}

void GameObject::draw(Color tint)
{
    // update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > xRows)
            frame = 0;
    }

    // Draw the character
    Rectangle source{ frame * width, 0.f, width, height };
    Rectangle dest{ worldPos.x, worldPos.y, scale * width, scale * height };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, tint);
}

bool GameObject::isOutOfBounds()
{
    return
        worldPos.x <= 0 ||
        worldPos.y <= 0 ||
        worldPos.x + width * scale > GameConfig::instance().screenWidth ||
        worldPos.y + height * scale > GameConfig::instance().screenHeight;
}

Rectangle GameObject::getHitbox()
{
    return Rectangle{
        worldPos.x,
        worldPos.y,
        width * scale,
        height * scale
    };
}
