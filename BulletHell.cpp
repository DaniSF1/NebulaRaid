#include <iostream>
#include "raylib.h"
#include "src/state/StateManager.h"
#include "src/state/MenuState.h"
#include "src/utils/GameConfig.h"

int main()
{
    int width = GameConfig::instance().screenWidth;
    int height = GameConfig::instance().screenHeight;
    InitWindow(width, height, "");

    StateManager stateManager;
    IManager* managerPtr = &stateManager;
    MenuState* menu = new MenuState(managerPtr);
    stateManager.setState(menu);

    SetTargetFPS(240);
    while (!WindowShouldClose())
    {
        stateManager.update();
    }
    CloseWindow();
}
