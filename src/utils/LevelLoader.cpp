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

    levelData.backgroundTexture = jsonData.value("backgroundTexture", "");
    levelData.musicTrack = jsonData.value("musicTrack", "");
    if(jsonData.contains("enemyWaves"))
    {
        for (const auto& waveJson : jsonData["enemyWaves"])
        {
            EnemyWave wave;
            wave.type = waveJson.value("enemyType", "");
            wave.count = waveJson.value("count", 0);
            wave.delay = waveJson.value("spawnDelay", 1.f);
            wave.startTime = waveJson.value("startTime", 0.f);
            levelData.waves.push_back(wave);
        }
    }

    return levelData;
}
