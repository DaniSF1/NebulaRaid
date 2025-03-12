#include "MenuState.h"
#include "raylib.h"
#include "TestState.h"
#include "Level1State.h"

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

	DrawText("Main Menu", 720/2 - 80, 200, 30, BLACK);
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
