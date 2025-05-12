#include "StateManager.h"

void StateManager::setState(IGameState* state)
{
    if(currentState) currentState->exitState();

    currentState.reset(state);
    currentState->enterState();
}

void StateManager::update()
{
    AudioManager::instance().update();
    currentState->update();
}
