#include "Level1State.h"
#include "raylib.h"
#include "MenuState.h"
#include "../utils/LevelLoader.h"
#include <iostream>

void Level1State::enterState()
{
	LevelData level = LevelLoader::loadLevel("json/lvl1.json");
	for (int i = 0; i < 1 /*level.enemyCount*/; i++)
	{
		Enemy* enemy = new Enemy();
		enemies.push_back(enemy);
	}
	map = LoadTexture("assets/ships/background/Background 2 Sprite Sheet.png");
}

void Level1State::exitState()
{
	player.unloadTexture();
	for (auto enemy : enemies)
	{
		enemy->unloadTexture();
	}
	UnloadTexture(map);
}

void Level1State::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

	grid.clearGrid();
	grid.insert(&player);
	for (Enemy* enemy : enemies)
	{
		grid.insert(enemy);
	}

	for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
	{
		grid.insert(bullet);
	}

	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}

	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : enemy->getBulletPool().getAllActiveObjects())
		{
			for (GameObject* obj : grid.getNearby(bullet))
			{
				Player* p = dynamic_cast<Player*>(obj);
				if (p && bullet->checkCollision(p)) 
				{
					bullet->handleCollision();
					p->takeDamage();
				}
			}
		}
	}

	for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
	{
		for (GameObject* obj : grid.getNearby(bullet))
		{
			Enemy* e = dynamic_cast<Enemy*>(obj);
			if (e && bullet->checkCollision(e)) 
			{
				bullet->handleCollision();
				e->takeDamage();
			}
		}
	}

	player.tick();

	for (auto enemy : enemies)
	{
		enemy->tick();
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
	}

#ifdef DEBUG_MODE
	grid.drawDebugGrid();
#endif // DEBUG_MODE


	EndDrawing();
}
