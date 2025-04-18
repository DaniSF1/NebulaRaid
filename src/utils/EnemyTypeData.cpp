#include "EnemyTypeData.h"
#include "../external/json.hpp"

EnemyTypeData loadEnemyType(const nlohmann::json& json)
{
	EnemyTypeData data;

	data.health = json.value("health", 10);
	data.speed = json.value("speed", 200.f);
	data.scale = json.value("scale", 2.f);
	data.movementType = json.value("movement", "RandomMovement");
	data.attackType = json.value("attack", "BasicAttackBehavior");
	data.retreatType = json.value("retreat", "BasicRetreatBehavior");
	data.texturePath = json.value("texture", "");
	data.bulletTexturePath = json.value("bulletTexture", "");

	return data;
}