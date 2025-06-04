#include "PlayState.h"
#include "GameOverState.h"

void PlayState::enterState()
{
	std::ifstream file("json/enemy_types.json");
	nlohmann::json jsonData;
	file >> jsonData;

	std::unordered_map<std::string, EnemyTypeData> enemyTypeMap;

	for (auto& pair : jsonData.items())
	{
		enemyTypeMap[pair.key()] = loadEnemyType(pair.value());
	}

	EnemyFactory::initialize(enemyTypeMap);
	EnemyFactory::loadSharedTextures();
	GameWorld::instance().setPlayer(&player);
	AudioManager::instance().playSound("startgame");
}

void PlayState::exitState()
{
	enemies.clear();
	EnemyFactory::unloadSharedTextures();
	AudioManager::instance().stopMusic();
	GameWorld::instance().setPlayer(nullptr);
	UnloadTexture(background);
}

void PlayState::update()
{
	//Background animation
	bPos.y += 120.f * GetFrameTime();
	if (bPos.y >= background.height * bScale) bPos.y = 0.0f;
	b2Pos.y = bPos.y - background.height * bScale;

	DrawTextureEx(background, bPos, 0.0, bScale, Fade(WHITE, 0.99f));
	DrawTextureEx(background, b2Pos, 0.0, bScale, Fade(WHITE, 0.99f));

	//Grid management
	grid.clearGrid();
	insertIntoGrid();

	//Player tick & elimination
	if (player.getActive())
	{
		player.tick();
	}
	else
	{
		GameWorld::instance().setPlayer(nullptr);
		AudioManager::instance().playSound("gameover");
		stateManager->setState(new GameOverState(stateManager));
		return;
	}

	//Enemy tick & elimination
	for (auto enemy : enemies)
	{
		enemy->tick();
	}

	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Enemy* enemy = *it;
		if (!enemy->getActive() && enemy->getBulletPool().getAllActiveObjects().size() == 0)
		{
			handleEnemyRemoval(enemy);
			it = enemies.erase(it);
		}
		else
		{
			++it;
		}
	}

	checkCollisions();

	DrawFPS(680, 10);
#ifdef DEBUG_MODE

	grid.drawDebugGrid();
#endif // DEBUG_MODE
}

void PlayState::insertIntoGrid()
{
	if (player.getActive())
	{
		grid.insert(&player);
		for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}
	for (Enemy* enemy : enemies)
	{
		grid.insert(enemy);
		for (Bullet* bullet : enemy->getBulletPool().getAllActiveObjects())
		{
			grid.insert(bullet);
		}
	}
}

void PlayState::checkCollisions()
{
	for (Enemy* enemy : enemies)
	{
		for (Bullet* bullet : enemy->getBulletPool().getAllActiveObjects())
		{
			for (GameObject* obj : grid.getNearby(bullet))
			{
				Player* p = dynamic_cast<Player*>(obj);
				if (p && bullet->checkCollision(p))
				{
					p->bulletCollision(bullet);
					enemy->getBulletPool().releaseObject(bullet);
					break;
				}
			}
		}
	}

	for (Bullet* bullet : player.getBulletPool().getAllActiveObjects())
	{
		for (GameObject* obj : grid.getNearby(bullet))
		{
			Enemy* e = dynamic_cast<Enemy*>(obj);
			if (e && bullet->checkCollision(e))
			{
				e->bulletCollision(bullet);
				player.getBulletPool().releaseObject(bullet);
				break;
			}
		}
	}
}
