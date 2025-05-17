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
	DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 30) / 2, GameConfig::instance().screenHeight / 6, 30, BLACK);
	DrawText("Controls:", screenWidth / 2 - MeasureText("Controls:", 30) / 2, GameConfig::instance().screenHeight / 4, 30, BLACK);
	DrawText("WASD for movement", screenWidth / 2 - MeasureText("WASD for movement", 30) / 2, GameConfig::instance().screenHeight / 4 + 40, 30, BLACK);
	DrawText("Space for shooting", screenWidth / 2 - MeasureText("Space for shooting", 30) / 2, GameConfig::instance().screenHeight / 4 + 80, 30, BLACK);
	DrawText("Press intro to start", screenWidth / 2 - MeasureText("Press intro to start", 30) / 2, GameConfig::instance().screenHeight / 2, 30, BLACK);
	
	if(IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new LevelState(stateManager));
	}

	EndDrawing();
}
