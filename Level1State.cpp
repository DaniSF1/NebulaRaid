#include "Level1State.h"
#include "raylib.h"
#include "MenuState.h"
#include "LevelLoader.h"
#include <iostream>

void Level1State::enterState()
{
	LevelData level = LevelLoader::loadLevel("json/lvl1.json");
	map = LoadTexture("assets/ships/Background 2 Sprite Sheet.png");
}

void Level1State::exitState()
{
	player.unloadTextures();
	UnloadTexture(map);
}

void Level1State::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

	player.tick();

	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

	EndDrawing();
}
