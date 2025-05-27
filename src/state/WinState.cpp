#include "WinState.h"

void WinState::enterState()
{

}

void WinState::exitState()
{

}

void WinState::update()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("You Won!", GameConfig::instance().screenWidth / 2 - MeasureText("You Won!", 30) / 2, GameConfig::instance().screenHeight / 6, 30, GREEN);
	DrawText("Press enter to return", GameConfig::instance().screenWidth / 2 - MeasureText("Press enter to return", 30) / 2, GameConfig::instance().screenHeight / 6 + 30, 30, GREEN);
	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

	EndDrawing();
}
