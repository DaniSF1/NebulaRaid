#pragma once
#include <string>
#include "../external/json.hpp"

struct LevelData
{
	int enemyCount;
	float spawnRateSeconds;
	int bulletPool;
};

class LevelLoader
{
public:
	static LevelData loadLevel(const std::string& filePath);
};

