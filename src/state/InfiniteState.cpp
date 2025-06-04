#include "InfiniteState.h"

void InfiniteState::enterState()
{
	PlayState::enterState();
	background = LoadTexture("assets/ships/background/Background 2 Sprite Sheet.png");
	AudioManager::instance().playMusic("assets/music/future.ogg");
	for (const std::string& type : spawnTypes)
	{
		enemyPools.emplace(std::piecewise_construct, std::forward_as_tuple(type), std::forward_as_tuple());
		for (int i = 0; i < 5; ++i)
		{
			auto enemy = EnemyFactory::create(type);
			enemyPools[type].addObject(std::move(enemy));
		}
	}
}

void InfiniteState::exitState()
{
	ScoreManager::instance().addScore("Player1", player.getScore(), 00);
	PlayState::exitState();
}

void InfiniteState::update()
{
	BeginDrawing();
	ClearBackground(WHITE);

	PlayState::update();
	if (GameWorld::instance().getPlayer() == nullptr)
	{
		EndDrawing(); 
		return;
	}

	timeSinceStart += GetFrameTime();
	float difficultyRatio = std::min(1.f, timeSinceStart / difficultyRampTime);
	spawnDelay = spawnDelayStart - difficultyRatio * (spawnDelayStart - spawnDelayMin);
	spawnTimer += GetFrameTime();

	if (timeSinceStart < 180.f) spawnTypes = { "basic", "sniper", "turret", "berserker" };
	else if (timeSinceStart < 210.f) spawnTypes = { "basic", "turret", "berserker" };
	else if (timeSinceStart < 240.f) spawnTypes = { "turret", "berserker" };
	else spawnTypes = { "berserker" };

	if (spawnTimer >= spawnDelay)
	{
		std::string type = spawnTypes[GetRandomValue(0, static_cast<int>(spawnTypes.size()) - 1)];
		spawnEnemy(type);
		spawnTimer = 0.f;
	}

	DrawText(TextFormat("Time: %.1f", timeSinceStart), 20, 60, 20, WHITE);
	DrawText(TextFormat("Spawn Delay: %.2f", spawnDelay), 20, 80, 20, WHITE);
	DrawText(TextFormat("Spawn Timer: %.2f", spawnTimer), 20, 100, 20, WHITE);

	EndDrawing();
}

void InfiniteState::spawnEnemy(std::string& type)
{
	auto it = enemyPools.find(type);
	if (it == enemyPools.end()) return;

	Enemy* enemy = it->second.getObject();
	if (!enemy) return;

	enemy->setWorldPos({ (float)GetRandomValue(0, GameConfig::instance().screenWidth - enemy->getWidth() * enemy->getScale()), -100.f });
	enemy->setActive(true);
	enemy->resetState();
	enemies.push_back(enemy);
}

void InfiniteState::handleEnemyRemoval(Enemy* enemy)
{
	const std::string& type = enemy->getType();
	auto it = enemyPools.find(type);
	if (it != enemyPools.end())
	{
		it->second.releaseObject(enemy);
	}
}
