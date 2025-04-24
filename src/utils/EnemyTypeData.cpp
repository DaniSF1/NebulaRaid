#include "EnemyTypeData.h"


EnemyTypeData loadEnemyType(const nlohmann::json& json)
{
	EnemyTypeData data;

	data.health = json.value("health", 10);
	data.speed = json.value("speed", 200.f);
	data.scale = json.value("scale", 2.f);
	data.targetY = json.value("initialY", 100.f);
	data.bulletDelay = json.value("bulletDelay", 0.1f);
	data.poolSize = json.value("poolSize", 10);
	data.movementType = json.value("movement", "RandomMovement");
	data.attackType = json.value("attack", "BasicAttackBehavior");
	data.retreatType = json.value("retreat", "BasicRetreatBehavior");
	data.texturePath = json.value("texture", "");
	data.bulletTexturePath = json.value("bulletTexture", "");

	return data;
}