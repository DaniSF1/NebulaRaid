#include "EnemyFactory.h"

std::unordered_map<std::string, EnemyTypeData> EnemyFactory::enemyTypes;
std::unordered_map<std::string, Texture2D> EnemyFactory::sharedTextures;
std::unordered_map<std::string, Texture2D> EnemyFactory::sharedBulletTextures;

void EnemyFactory::initialize(const std::unordered_map<std::string, EnemyTypeData>& types)
{
	enemyTypes = types;
}

std::unique_ptr<Enemy> EnemyFactory::create(const std::string& typeName)
{
	const EnemyTypeData& data = enemyTypes[typeName];
	auto enemy = std::make_unique<Enemy>(data.poolSize);

	enemy->setHealth(data.health);
	enemy->setMaxHealth(data.health);
	enemy->setSpeed(data.speed);
	enemy->setScale(data.scale);
	enemy->setTexture(sharedTextures[data.texturePath]);
	enemy->setBulletTexture(sharedBulletTextures[data.bulletTexturePath]);
	enemy->setWidth(enemy->getTexture().width / enemy->getXRows());
	enemy->setHeight(enemy->getTexture().height / enemy->getYRows());
	enemy->setWorldPos({ (float)GetRandomValue(0, GameConfig::instance().screenWidth - (enemy->getTexture().width * enemy->getScale())), -100.f });
	enemy->setHitbox(Rectangle{ enemy->getWorldPos().x, enemy->getWorldPos().y, enemy->getWidth(), enemy->getHeight() });
	enemy->setDamage(data.damage);
	enemy->setBulletSpeed(data.bulletSpeed);
	enemy->setScore(data.score);
	enemy->setType(typeName);

	//Movement
	enemy->setEnterBehavior(std::make_unique<EnterTopBehavior>(data.targetY));
	if (data.movementType == "RandomMovement") enemy->setMovementBehavior(std::make_unique<RandomMovement>());
	else if (data.movementType == "LateralMovement") enemy->setMovementBehavior(std::make_unique<LateralMovement>());
	else if (data.movementType == "StaticMovement") enemy->setMovementBehavior(std::make_unique<StaticMovement>());
	else if (data.movementType == "BerserkerMovement") enemy->setMovementBehavior(std::make_unique<BerserkerMovement>());
	enemy->setRetreatBehavior(std::make_unique<BasicRetreatBehavior>());

	//Attack
	if (data.attackType == "BasicAttackBehavior") enemy->setAttackBehavior(std::make_unique<BasicAttackBehavior>(data.bulletDelay));
	else if (data.attackType == "PrecisionAttack") enemy->setAttackBehavior(std::make_unique<PrecisionAttack>(data.bulletDelay));
	else if (data.attackType == "TurretAttack") enemy->setAttackBehavior(std::make_unique<TurretAttack>(data.bulletDelay));
	else if (data.attackType == "Berserker") enemy->setAttackBehavior(std::make_unique<BerserkerAttack>(data.bulletDelay));

	return enemy;
}

void EnemyFactory::loadSharedTextures()
{
	for (auto& pair : enemyTypes) 
	{
		if (sharedTextures.find(pair.second.texturePath) == sharedTextures.end())
		{
			sharedTextures[pair.second.texturePath] = LoadTexture(pair.second.texturePath.c_str());
		}
		if (sharedBulletTextures.find(pair.second.bulletTexturePath) == sharedBulletTextures.end())
		{
			sharedBulletTextures[pair.second.bulletTexturePath] = LoadTexture(pair.second.bulletTexturePath.c_str());
		}
	}

}

void EnemyFactory::unloadSharedTextures()
{
	for (auto& texture : sharedTextures)
	{
		UnloadTexture(texture.second);
	}
	for (auto& texture : sharedBulletTextures)
	{
		UnloadTexture(texture.second);
	}
	sharedTextures.clear();
	sharedBulletTextures.clear();
}
