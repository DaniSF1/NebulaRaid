#pragma once
#include "PlayState.h"

class InfiniteState : public PlayState
{
public:
	InfiniteState(IManager* managerReference) : PlayState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;

protected:
	void spawnEnemy(std::string& type) override;
	void handleEnemyRemoval(Enemy* enemy) override;

private:
	std::unordered_map<std::string, Pool<Enemy>> enemyPools;
	float spawnTimer = 0.f;
	float timeSinceStart = 0.f;
	float spawnDelay = 4.f;
	const float spawnDelayStart = 5.f;
	const float spawnDelayMin = 2.f;
	const float difficultyRampTime = 180.f;

	std::vector<std::string> spawnTypes = { "basic", "sniper", "turret", "berserker" };
};