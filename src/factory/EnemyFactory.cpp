#include "EnemyFactory.h"


std::unordered_map<std::string, EnemyTypeData> EnemyFactory::enemyTypes;
std::unordered_map<std::string, Texture2D> EnemyFactory::sharedTextures;
std::unordered_map<std::string, Texture2D> EnemyFactory::sharedBulletTextures;

void EnemyFactory::initialize(const std::unordered_map<std::string, EnemyTypeData>& types)
{
	enemyTypes = types;
}

Enemy* EnemyFactory::create(const std::string& typeName)
{
	const EnemyTypeData& data = enemyTypes[typeName];
	Enemy* enemy = new Enemy(data.poolSize);

	enemy->setHealth(data.health);
	enemy->setSpeed(data.speed);
	enemy->setScale(data.scale);
	enemy->setTexture(sharedTextures[data.texturePath]);
	enemy->setBulletTexture(sharedBulletTextures[data.bulletTexturePath]);
	enemy->setWidth(enemy->getTexture().width / enemy->getXRows());
	enemy->setHeight(enemy->getTexture().height / enemy->getYRows());
	enemy->setWorldPos({ (float)GetRandomValue(0, GameConfig::instance().screenWidth - (enemy->getTexture().width * enemy->getScale())), -100.f });
	enemy->setHitbox(Rectangle{ enemy->getWorldPos().x, enemy->getWorldPos().y, enemy->getWidth(), enemy->getHeight() });

	//Movement
	enemy->setEnterBehavior(new EnterTopBehavior(data.targetY));
	if (data.movementType == "RandomMovement") enemy->setMovementBehavior(new RandomMovement());
	else if (data.movementType == "LateralMovement") enemy->setMovementBehavior(new LateralMovement());
	else if (data.movementType == "StaticMovement") enemy->setMovementBehavior(new StaticMovement());
	else if (data.movementType == "BerserkerMovement") enemy->setMovementBehavior(new BerserkerMovement());
	enemy->setRetreatBehavior(new BasicRetreatBehavior());

	//Attack
	if (data.attackType == "BasicAttackBehavior") enemy->setAttackBehavior(new BasicAttackBehavior(data.bulletDelay));
	else if (data.attackType == "PrecisionAttack") enemy->setAttackBehavior(new PrecisionAttack(data.bulletDelay));
	else if (data.attackType == "TurretAttack") enemy->setAttackBehavior(new TurretAttack(data.bulletDelay));
	else if (data.attackType == "Berserker") enemy->setAttackBehavior(new BerserkerAttack(data.bulletDelay));

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
