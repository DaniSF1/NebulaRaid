#include "LevelState.h"

void LevelState::enterState()
{
	loadLevel(levelPaths[currentLevelIndex]);
	PlayState::enterState();
}

void LevelState::exitState()
{
	ScoreManager::instance().addScore("Player1", player.getScore(), currentLevelIndex);
	ownedEnemies.clear();
	PlayState::exitState();
}

void LevelState::update()
{
	BeginDrawing();
	ClearBackground(WHITE);
	
	PlayState::update();

	if (GameWorld::instance().getPlayer() == nullptr)
	{
		EndDrawing();
		return;
	}
	
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

	if (isTransitioning)
	{
		levelTransitionTimer -= GetFrameTime();

		int screenWidth = GameConfig::instance().screenWidth;
		int screenHeight = GameConfig::instance().screenHeight;
		DrawText("Level cleared!", screenWidth / 2 - MeasureText("Level cleared!", 40) / 2, screenHeight / 6, 40, WHITE);
		DrawText("Loading next level...", screenWidth / 2 - MeasureText("Loading next level...", 40) / 2, screenHeight / 6 + 40, 40, WHITE);
		AudioManager::instance().stopMusic();
		if (levelTransitionTimer <= 0.f)
		{
			isTransitioning = false;
			resetLevel();
		}
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
			player.setScore(player.getScore() + (1000 * currentLevelIndex));
		}
		else
		{
			AudioManager::instance().playSound("win");
			stateManager->setState(new WinState(stateManager));
		}
	}
	EndDrawing();
}

void LevelState::spawnEnemy(std::string& type)
{
	auto enemy = EnemyFactory::create(type);
	enemies.push_back(enemy.get());
	ownedEnemies.push_back(std::move(enemy));
}

void LevelState::handleEnemyRemoval(Enemy* enemy)
{
	auto it = std::find_if(ownedEnemies.begin(), ownedEnemies.end(), [enemy](const std::unique_ptr<Enemy>& ptr) { return ptr.get() == enemy; });
	if (it != ownedEnemies.end())
	{
		ownedEnemies.erase(it);
	}
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
	ownedEnemies.clear();
	enemies.clear();

	UnloadTexture(background);
	background = {};

	levelCompleted = false;
	timeSinceLevelStart = 0.f;
	remainingEnemies = 0;

	int newHealth;
	if (player.getHealth() + 40 + 20 * currentLevelIndex < 250) newHealth = player.getHealth() + 40 + 20 * currentLevelIndex;
	else newHealth = 250;
	player.setHealth(newHealth);

	loadLevel(levelPaths[currentLevelIndex]);
}
