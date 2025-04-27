#pragma once
#include <string>
#include "../external/json.hpp"

struct EnemyTypeData
{
	int health;
	float speed;
	float scale;
	float targetY;
	float bulletDelay;
	int poolSize;
	std::string movementType;
	std::string attackType;
	std::string retreatType;
	std::string texturePath;
	std::string bulletTexturePath;
};

EnemyTypeData loadEnemyType(const nlohmann::json& json);