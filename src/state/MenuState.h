#pragma once
#include "AViewState.h"
#include "raylib.h"
#include "TestState.h"
#include "LevelState.h"
#include "../utils/GameConfig.h"

class MenuState : public AViewState
{
public:
	MenuState(IManager* managerReference) : AViewState(managerReference){}
	void enterState() override;
	void exitState() override;
	void update() override;
};

