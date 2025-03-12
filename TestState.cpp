#include "TestState.h"
#include "raylib.h"
#include "MenuState.h"

void TestState::enterState()
{
}

void TestState::exitState()
{
}

void TestState::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	DrawText("Test Scene", 720 / 2 - 80, 200, 30, BLACK);
	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

	EndDrawing();
}
