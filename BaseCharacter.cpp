#include "BaseCharacter.h"

void BaseCharacter::tick()
{
    // update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    lastFrameWorldPos = worldPos;

    // Draw the character
    Rectangle source{ frame * width, 0.f, width, height };
    Rectangle dest{ worldPos.x, worldPos.y, scale * width, scale * height };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement()
{
	worldPos = lastFrameWorldPos;
}

void BaseCharacter::unloadTextures()
{
    UnloadTexture(texture);
    UnloadTexture(bulletTexture);
}

Rectangle BaseCharacter::getHitbox()
{
	return Rectangle{
		worldPos.x,
		worldPos.y,
		width * scale,
		height * scale
	};
}
