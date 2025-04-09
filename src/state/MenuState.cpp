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

	DrawText("Main Menu", GameConfig::instance().screenWidth/2 - 80, GameConfig::instance().screenHeight / 6, 30, BLACK);
	if(IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new Level1State(stateManager));
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		stateManager->setState(new TestState(stateManager));
	}

	EndDrawing();
}
