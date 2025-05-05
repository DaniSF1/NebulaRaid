#include "LevelState.h"

void LevelState::enterState()
{
	level = LevelLoader::loadLevel("json/lvl1.json");
	background = LoadTexture(level.backgroundTexture.c_str());
	
	for (auto& levelWave : level.waves)
	{
		ActiveWave wave = ActiveWave();
		wave.wave = levelWave;
		waves.push_back(wave);
		remainingEnemies += levelWave.count;
	}

	std::ifstream file("json/enemy_types.json");
	nlohmann::json jsonData;
	file >> jsonData;

	std::unordered_map<std::string, EnemyTypeData> enemyTypeMap;

	for (auto& pair : jsonData.items())
	{
		enemyTypeMap[pair.key()] = loadEnemyType(pair.value());
	}

	EnemyFactory::initialize(enemyTypeMap);
	EnemyFactory::loadSharedTextures();

	GameWorld::instance().setPlayer(&player);
}

void LevelState::exitState()
{
	player.~Player();
	for (auto enemy : enemies)
	{
		delete enemy;
	}

	enemies.clear();
	EnemyFactory::unloadSharedTextures();
	UnloadTexture(background);
}

void LevelState::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	//Background animation
	bPos.y += 120.f * GetFrameTime();
	if (bPos.y >= background.height * bScale) bPos.y = 0.0f;
	b2Pos.y = bPos.y - background.height * bScale;

	DrawTextureEx(background, bPos, 0.0, bScale, Fade(WHITE, 0.99f));
	DrawTextureEx(background, b2Pos, 0.0, bScale, Fade(WHITE, 0.99f));

	//Grid management
	grid.clearGrid();
	insertIntoGrid();
	checkCollisions();

	//Spawn enemies
	timeSinceLevelStart += GetFrameTime();
	for (auto& wave : waves)
	{
		if (timeSinceLevelStart >= wave.wave.startTime)
		{
			wave.timeSinceLastSpawn += GetFrameTime();

			if (wave.spawnedCount < wave.wave.count && wave.timeSinceLastSpawn >= wave.wave.delay)
			{
				spawnEnemy(wave.wave.type);
				wave.timeSinceLastSpawn = 0.f;
				wave.spawnedCount++;
				remainingEnemies--;
			}
		}
	}

	//Player tick & elimination
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

	//Enemy tick & elimination
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
	
	//End level
	if (remainingEnemies == 0 && enemies.size() == 0)
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

void LevelState::insertIntoGrid()
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

void LevelState::checkCollisions()
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

void LevelState::spawnEnemy(std::string& type)
{
	Enemy* enemy = EnemyFactory::create(type);
	enemies.push_back(enemy);
}
