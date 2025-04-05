#pragma once
#include "AViewState.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../core/SpatialGrid.h"
#include <vector>

class Level1State : public AViewState
{
public:
	Level1State(IManager* managerReference) : AViewState(managerReference), grid(720, 1280, 128) {}
	void enterState() override;
	void exitState() override;
	void update() override;

private:
	Player player;
	std::vector<Enemy*> enemies;
	Texture2D map{};
	Vector2 mapPos{ 0.0f,0.0f };
	const float mapScale = 1.25f;
	SpatialGrid grid;
};

