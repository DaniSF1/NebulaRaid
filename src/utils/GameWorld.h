#pragma once

#include "../entities/Player.h"

class GameWorld
{
public:
	static GameWorld& instance()
	{
		static GameWorld instance;
		return instance;
	}

	Player* getPlayer() const { return player; }
	void setPlayer(Player* p) { player = p; }

private:
	GameWorld() = default;
	Player* player = nullptr;
};