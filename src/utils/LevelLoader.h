#pragma once
#include <string>
#include "../external/json.hpp"

struct LevelData
{
	int enemyCount;
	int spawnRateMs;
	int bulletPool;
};

class LevelLoader
{
public:
	static LevelData loadLevel(const std::string& filePath);
};

