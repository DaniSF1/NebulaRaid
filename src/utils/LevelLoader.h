#pragma once
#include <string>
#include "../external/json.hpp"

struct EnemyWave
{
	std::string type;
	int count;
	float delay;
	float startTime;
};

struct LevelData
{
	std::string backgroundTexture;
	std::string musicTrack;
	std::vector<EnemyWave> waves;
};

class LevelLoader
{
public:
	static LevelData loadLevel(const std::string& filePath);
};