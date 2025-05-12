#include "LevelState.h"

void LevelState::enterState()
{
	loadLevel(levelPaths[currentLevelIndex]);

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

	AudioManager::instance().playSound("startgame");
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
	AudioManager::instance().stopMusic();
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
		AudioManager::instance().playSound("gameover");
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
		if (!enemy->getActive() && enemy->getBulletPool().getAllActiveObjects().size() == 0)
		{
			delete enemy;
			it = enemies.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (isTransitioning)
	{
		levelTransitionTimer -= GetFrameTime();

		DrawText("Level cleared!", GameConfig::instance().screenWidth / 2 - 200, GameConfig::instance().screenHeight / 6, 40, WHITE);
		DrawText("Loading next level...", GameConfig::instance().screenWidth / 2 - 200, GameConfig::instance().screenHeight / 4, 40, WHITE);
		AudioManager::instance().stopMusic();
		if (levelTransitionTimer <= 0.f)
		{
			isTransitioning = false;
			resetLevel();
		}
		EndDrawing();
		return;
	}
	
	//End level
	if (!levelCompleted && remainingEnemies == 0 && enemies.size() == 0)
	{
		currentLevelIndex++;
		if (currentLevelIndex < levelPaths.size())
		{
			isTransitioning = true;
			levelTransitionTimer = levelTransitionDelay;
			levelCompleted = true;
		}
		else
		{
			AudioManager::instance().playSound("win");
			stateManager->setState(new WinState(stateManager));
			EndDrawing();
			return;
		}
	}

	DrawFPS(680, 10);
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

void LevelState::loadLevel(const std::string& levelPath)
{
	level = LevelLoader::loadLevel(levelPath);
	background = LoadTexture(level.backgroundTexture.c_str());
	AudioManager::instance().playMusic(level.musicTrack);

	waves.clear();
	for (auto& levelWave : level.waves)
	{
		ActiveWave wave = ActiveWave();
		wave.wave = levelWave;
		waves.push_back(wave);
		remainingEnemies += levelWave.count;
	}
}

void LevelState::resetLevel()
{
	AudioManager::instance().playSound("nextLevel");
	for (auto enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();

	UnloadTexture(background);
	background = {};

	levelCompleted = false;
	timeSinceLevelStart = 0.f;
	remainingEnemies = 0;

	float newHealth;
	if (player.getHealth() + 40.f + 20.f * currentLevelIndex < 250.f) newHealth = player.getHealth() + 40.f + 20.f * currentLevelIndex;
	else newHealth = 250.f;
	player.setHealth(newHealth);

	loadLevel(levelPaths[currentLevelIndex]);
}
