#include <iostream>
#include "raylib.h"
#include "src/state/StateManager.h"
#include "src/state/MenuState.h"
#include "src/utils/AudioManager.h"
#include "src/utils/GameConfig.h"
#include "src/utils/ScoreManager.h"

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
    ScoreManager::instance().load();
    AudioManager::instance().init();
    AudioManager::instance().playMusic("assets/music/16_bit_space.ogg");
    while (!WindowShouldClose())
    {
        stateManager.update();
    }

    AudioManager::instance().unload();
    CloseWindow();
}
