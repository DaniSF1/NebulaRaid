#pragma once
#include "AViewState.h"
#include "raylib.h"
#include "MenuState.h"

class GameOverState : public AViewState
{
public:
	GameOverState(IManager* managerReference) : AViewState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;
};

