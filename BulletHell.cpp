#include <iostream>
#include "raylib.h"
#include "src/state/StateManager.h"
#include "src/state/MenuState.h"

int main()
{
    int width = 720;
    int height = 1280;
    InitWindow(width, height, "");

    StateManager stateManager;
    IManager* managerPtr = &stateManager;
    MenuState* menu = new MenuState(managerPtr);
    stateManager.setState(menu);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        stateManager.update();
    }
    CloseWindow();
}
