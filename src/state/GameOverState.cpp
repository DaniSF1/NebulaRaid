#include "GameOverState.h"


void GameOverState::enterState()
{

}

void GameOverState::exitState()
{

}

void GameOverState::update()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("Game Over", 720 / 2 - 80, 200, 30, RED);
	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

	EndDrawing();
}
