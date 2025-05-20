#pragma once
#include "PlayState.h"

class InfiniteState : public PlayState
{
public:
	InfiniteState(IManager* managerReference) : PlayState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;

	//Spawn Methods

private:
	//Spawn Variables
};