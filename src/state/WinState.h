#pragma once
#include "AViewState.h"
#include "raylib.h"
#include "MenuState.h"

class WinState : public AViewState
{
public:
	WinState(IManager* managerReference) : AViewState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;
};