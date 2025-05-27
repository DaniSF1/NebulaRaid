#pragma once
#include "AViewState.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../core/SpatialGrid.h"
#include "../utils/EnemyTypeData.h"
#include "../utils/GameConfig.h"
#include "../utils/GameWorld.h"
#include "../utils/ScoreManager.h"
#include "../utils/AudioManager.h"
#include "../factory/EnemyFactory.h"
#include <iostream>
#include <fstream>


class PlayState : public AViewState
{
public:
	PlayState(IManager* managerReference) : AViewState(managerReference), grid(GameConfig::instance().screenWidth, GameConfig::instance().screenHeight, GameConfig::instance().gridCellSize) {}
	void enterState() override;
	void exitState() override;
	void update() override;

protected:
	Player player;
	std::vector<Enemy*> enemies;
	Texture2D background{};

	virtual void spawnEnemy(std::string& type) = 0;
	virtual void handleEnemyRemoval(Enemy* enemy) = 0;
	void insertIntoGrid();
	void checkCollisions();

private:
	SpatialGrid grid;
	Vector2 bPos{ 0.0f, 0.0f };
	Vector2 b2Pos{ 0.0f, 0.0f };
	const float bScale = 1.25f;
};