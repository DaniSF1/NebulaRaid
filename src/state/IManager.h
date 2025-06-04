#pragma once

class IManager 
{
public:
	virtual void setState(IGameState* state) = 0;
	virtual void update() = 0;
	virtual ~IManager() = default;
};