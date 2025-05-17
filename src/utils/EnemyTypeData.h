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
	float damage;
	float bulletSpeed;
	int poolSize;
	int score;
	std::string movementType;
	std::string attackType;
	std::string retreatType;
	std::string texturePath;
	std::string bulletTexturePath;
};

EnemyTypeData loadEnemyType(const nlohmann::json& json);