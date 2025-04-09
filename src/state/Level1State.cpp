#include "Level1State.h"

void Level1State::enterState()
{
	LevelData level = LevelLoader::loadLevel("json/lvl1.json");

	Enemy::LoadSharedTexture();
	for (int i = 0; i < level.enemyCount; i++)
	{
		Enemy* enemy = new Enemy();
		enemies.push_back(enemy);
	}
	map = LoadTexture("assets/ships/background/Background 2 Sprite Sheet.png");
}

void Level1State::exitState()
{
	player.~Player();
	for (auto enemy : enemies)
	{
		delete enemy;
	}

	enemies.clear();
	Enemy::UnloadSharedTexture();
	UnloadTexture(map);
}

void Level1State::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

	grid.clearGrid();
	insertIntoGrid();
	checkCollisions();

	if (player.getActive())
	{
		player.tick();
	}
	else
	{
		stateManager->setState(new GameOverState(stateManager));
		EndDrawing();
		return;
	}

	for (auto enemy : enemies)
	{
		enemy->tick();
	}

	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Enemy* enemy = *it;
		if (!enemy->getActive())
		{
			delete enemy;
			it = enemies.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		stateManager->setState(new MenuState(stateManager));
		EndDrawing();
		return;
	}
	
#ifdef DEBUG_MODE
	grid.drawDebugGrid();
#endif // DEBUG_MODE


	EndDrawing();
}

void Level1State::insertIntoGrid()
{
	if (player.getActive())
	{
		grid.insert(&player);
	}
	for (Enemy* enemy : enemies)
	{
		grid.insert(enemy);
	}

	if (player.getActive()) 
	{
		for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}

	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}
}

void Level1State::checkCollisions()
{
	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : enemy->getBulletPool().getAllActiveObjects())
		{
			for (GameObject* obj : grid.getNearby(bullet))
			{
				Player* p = dynamic_cast<Player*>(obj);
				if (p && bullet->checkCollision(p))
				{
					p->bulletCollision(bullet);
					enemy->getBulletPool().releaseObject(bullet);
					break;
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
				e->bulletCollision(bullet);
				player.getBulletPool().releaseObject(bullet);
				break;
			}
		}
	}
}
