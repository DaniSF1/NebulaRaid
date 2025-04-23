#pragma once
#include "AViewState.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../core/SpatialGrid.h"
#include "../utils/LevelLoader.h"
#include "../utils/EnemyTypeData.h"
#include "../utils/GameConfig.h"
#include "../utils/GameWorld.h"
#include "../factory/EnemyFactory.h"
#include "raylib.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "WinState.h"
#include <vector>
#include <iostream>
#include <fstream>

class Level1State : public AViewState
{
public:
	Level1State(IManager* managerReference) : AViewState(managerReference), grid(GameConfig::instance().screenWidth, GameConfig::instance().screenHeight, GameConfig::instance().gridCellSize) {}
	void enterState() override;
	void exitState() override;
	void update() override;
	void insertIntoGrid();
	void checkCollisions();
	void spawnEnemy();

private:
	Player player;
	std::vector<Enemy*> enemies;
	Texture2D background{};
	Vector2 bPos{ 0.0f, 0.0f };
	Vector2 b2Pos{ 0.0f, 0.0f };
	const float bScale = 1.25f;
	SpatialGrid grid;

	float timeSinceSpawned = 1.5f;
	LevelData level;
};

