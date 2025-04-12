#include "LevelLoader.h"
#include <fstream>
#include <iostream>

LevelData LevelLoader::loadLevel(const std::string& filePath)
{
    LevelData levelData{};

    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        std::cerr << "Error: File not open" << filePath << std::endl;
        return levelData;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    levelData.enemyCount = jsonData.value("enemyCount", 0);
    levelData.spawnRateSeconds = jsonData.value("spawnRateMs", 1000) / 1000.f;
    levelData.bulletPool = jsonData.value("bulletPool", 500);

    return levelData;
}
