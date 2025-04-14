#include "Level1State.h"

void Level1State::enterState()
{
	level = LevelLoader::loadLevel("json/lvl1.json");

	Enemy::LoadSharedTexture();
	background = LoadTexture("assets/ships/background/Background 2 Sprite Sheet.png");
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
	UnloadTexture(background);
}

void Level1State::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	bPos.y += 120.f * GetFrameTime();
	if (bPos.y >= background.height * bScale) bPos.y = 0.0f;
	b2Pos.y = bPos.y - background.height * bScale;

	DrawTextureEx(background, bPos, 0.0, bScale, WHITE);
	DrawTextureEx(background, b2Pos, 0.0, bScale, WHITE);

	grid.clearGrid();
	insertIntoGrid();
	checkCollisions();

	timeSinceSpawned += GetFrameTime();
	if (timeSinceSpawned >= level.spawnRateSeconds && level.enemyCount != 0)
	{
		timeSinceSpawned = 0.0f;
		level.enemyCount--;
		spawnEnemy();
	}

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
	
	if (level.enemyCount == 0 && enemies.size() == 0)
	{
		stateManager->setState(new WinState(stateManager));
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
		for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}
	for (Enemy* enemy : enemies)
	{
		grid.insert(enemy);
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

void Level1State::spawnEnemy()
{
	Enemy* enemy = new Enemy();
	enemies.push_back(enemy);
}
