#pragma once

#include "../utils/EnemyTypeData.h"
#include "../entities/Enemy.h"
#include <string>
#include <unordered_map>

class EnemyFactory
{
public:
	static void initialize(const std::unordered_map<std::string, EnemyTypeData>& types);
	static Enemy* create(const std::string& typeName);

	static void loadSharedTextures();
	static void unloadSharedTextures();

private:
	static std::unordered_map<std::string, EnemyTypeData> enemyTypes;
	static std::unordered_map<std::string, Texture2D> sharedTextures;
};