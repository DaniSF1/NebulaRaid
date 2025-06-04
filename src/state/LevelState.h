#pragma once

#include "PlayState.h"
#include "../utils/LevelLoader.h"
#include "WinState.h"
#include <memory>
#include <algorithm>


struct ActiveWave
{
	EnemyWave wave;
	float timeSinceLastSpawn = 0.f;
	int spawnedCount = 0;
};

class LevelState : public PlayState
{
public:
	LevelState(IManager* managerReference) : PlayState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;

	void loadLevel(const std::string& levelPath);
	void resetLevel();

protected:
	void spawnEnemy(std::string& type) override;
	void handleEnemyRemoval(Enemy* enemy) override;

private:
	std::vector<ActiveWave> waves;
	float timeSinceLevelStart = 0.f;
	int remainingEnemies = 0;
	LevelData level;

	std::vector<std::unique_ptr<Enemy>> ownedEnemies;

	int currentLevelIndex = 0;
	bool levelCompleted = false;
	bool isTransitioning = false;
	float levelTransitionTimer = 0.f;
	const float levelTransitionDelay = 5.f;
	std::vector<std::string> levelPaths = { "json/lvl1.json", "json/lvl2.json", "json/lvl3.json", "json/lvl4.json", "json/lvl5.json" };
};

