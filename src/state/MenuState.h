#pragma once
#include "AViewState.h"

class MenuState : public AViewState
{
public:
	MenuState(IManager* managerReference) : AViewState(managerReference){}
	void enterState() override;
	void exitState() override;
	void update() override;
};

