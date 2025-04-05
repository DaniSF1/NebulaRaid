#pragma once
#include "IGameState.h"
#include "IManager.h"
#include <memory>

class StateManager : public IManager
{
public:
	void setState(IGameState* state) override;
	void update() override;

private:
	std::unique_ptr<IGameState> currentState = nullptr;
};

