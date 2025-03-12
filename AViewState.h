#pragma once
#include "IGameState.h"
#include "IManager.h"

class AViewState : public IGameState
{
public:
	AViewState(IManager* managerReference) : stateManager(managerReference) {}

	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void update() = 0;
protected:
	IManager* stateManager;
};