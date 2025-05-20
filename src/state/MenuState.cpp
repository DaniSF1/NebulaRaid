#include "MenuState.h"

void MenuState::enterState()
{

}

void MenuState::exitState()
{

}

void MenuState::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	int screenWidth = GameConfig::instance().screenWidth;
	int screenHeight = GameConfig::instance().screenHeight;
	DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 30) / 2, screenHeight / 6, 30, BLACK);
	DrawText("Controls:", screenWidth / 2 - MeasureText("Controls:", 30) / 2, screenHeight / 4, 30, BLACK);
	DrawText("WASD for movement", screenWidth / 2 - MeasureText("WASD for movement", 30) / 2, screenHeight / 4 + 40, 30, BLACK);
	DrawText("Space for shooting", screenWidth / 2 - MeasureText("Space for shooting", 30) / 2, screenHeight / 4 + 80, 30, BLACK);
	DrawText("Press intro to start: Level Mode", screenWidth / 2 - MeasureText("Press intro to start: Level Mode", 30) / 2, screenHeight / 2, 30, BLACK);
	DrawText("Press space to start: Infinite Mode", screenWidth / 2 - MeasureText("Press space to start: Infinite Mode", 30) / 2, screenHeight / 2 + 40, 30, BLACK);

	if(IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new LevelState(stateManager));
	}

	EndDrawing();
}
