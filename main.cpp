#include "src/game_engine.h"
#include "src/controller.h"
#include "src/ux.h"
#include <iostream>

int main()
{

    int choice = runUXMenu();

    if (choice == 1)
    {
        GameEngine engine;
        Controller ctrl(engine);
        ctrl.loop();
    }
    return 0;
}