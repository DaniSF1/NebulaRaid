#pragma once
#include "AViewState.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../core/SpatialGrid.h"
#include "../utils/LevelLoader.h"
#include "../utils/EnemyTypeData.h"
#include "../utils/GameConfig.h"
#include "../utils/GameWorld.h"
#include "../utils/ScoreManager.h"
#include "../utils/AudioManager.h"
#include "../factory/EnemyFactory.h"
#include "raylib.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "WinState.h"
#include <vector>
#include <iostream>
#include <fstream>


struct ActiveWave
{
	EnemyWave wave;
	float timeSinceLastSpawn = 0.f;
	int spawnedCount = 0;
};

class LevelState : public AViewState
{
public:
	LevelState(IManager* managerReference) : AViewState(managerReference), grid(GameConfig::instance().screenWidth, GameConfig::instance().screenHeight, GameConfig::instance().gridCellSize) {}
	void enterState() override;
	void exitState() override;
	void update() override;
	void insertIntoGrid();
	void checkCollisions();
	void spawnEnemy(std::string& type);
	void loadLevel(const std::string& levelPath);
	void resetLevel();

private:
	Player player;
	Texture2D background{};
	Vector2 bPos{ 0.0f, 0.0f };
	Vector2 b2Pos{ 0.0f, 0.0f };
	const float bScale = 1.25f;
	SpatialGrid grid;

	std::vector<Enemy*> enemies;
	std::vector<ActiveWave> waves;
	float timeSinceLevelStart = 0.f;
	int remainingEnemies = 0;
	LevelData level;

	int currentLevelIndex = 0;
	bool levelCompleted = false;
	bool isTransitioning = false;
	float levelTransitionTimer = 0.f;
	const float levelTransitionDelay = 5.f;
	std::vector<std::string> levelPaths = { "json/lvl1.json", "json/lvl2.json", "json/lvl3.json", "json/lvl4.json", "json/lvl5.json" };
};

