#pragma once

#include "../utils/EnemyTypeData.h"
#include "../entities/Enemy.h"
#include "../behaviors/BasicAttackBehavior.h"
#include "../behaviors/BasicRetreatBehavior.h"
#include "../behaviors/BerserkerAttack.h"
#include "../behaviors/BerserkerMovement.h"
#include "../behaviors/EnterTopBehavior.h"
#include "../behaviors/LateralMovement.h"
#include "../behaviors/PrecisionAttack.h"
#include "../behaviors/RandomMovement.h"
#include "../behaviors/TurretAttack.h"
#include "../behaviors/StaticMovement.h"
#include <string>
#include <unordered_map>
#include <memory>

class EnemyFactory
{
public:
	static void initialize(const std::unordered_map<std::string, EnemyTypeData>& types);
	static std::unique_ptr<Enemy> create(const std::string& typeName);

	static void loadSharedTextures();
	static void unloadSharedTextures();

private:
	static std::unordered_map<std::string, EnemyTypeData> enemyTypes;
	static std::unordered_map<std::string, Texture2D> sharedTextures;
	static std::unordered_map<std::string, Texture2D> sharedBulletTextures;
};