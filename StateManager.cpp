#include "StateManager.h"


void StateManager::setState(IGameState* state)
{
    if(currentState) currentState->exitState();

    currentState.reset(state);
    currentState->enterState();
}

void StateManager::update()
{
    currentState->update();
}
