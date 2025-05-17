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

	DrawText("Game Over", GameConfig::instance().screenWidth / 2 - MeasureText("Game Over", 30) / 2, GameConfig::instance().screenHeight / 6, 30, RED);
	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

	EndDrawing();
}
