#pragma once
#include "AViewState.h"
#include "Player.h"

class Level1State : public AViewState
{
public:
	Level1State(IManager* managerReference) : AViewState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;

private:
	Player player;
	Texture2D map{};
	Vector2 mapPos{ 0.0f,0.0f };
	const float mapScale = 1.25f;
};

