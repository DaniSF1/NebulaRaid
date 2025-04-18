#pragma once
#include <string>

struct EnemyTypeData
{
	int health;
	float speed;
	float scale;
	std::string movementType;
	std::string attackType;
	std::string retreatType;
	std::string texturePath;
	std::string bulletTexturePath;
};