#pragma once

class IGameState
{
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void update() = 0;
	virtual ~IGameState() = default;
};