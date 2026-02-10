#include "game_engine.h"

#include <iostream>

int main() {
    GameEngine game;

    game.initialize();
    game.run();
    game.shutdown();

    return 0;
}
