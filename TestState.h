#pragma once
#include "AViewState.h"

class TestState : public AViewState
{
public:
	TestState(IManager* managerReference) : AViewState(managerReference) {}
	void enterState() override;
	void exitState() override;
	void update() override;
};

