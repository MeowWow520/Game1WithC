#include "Game.h"

Game::Game() {
    spdlog::info(u8"Game::Game() initialized");
}

Game::~Game() {
    spdlog::info(u8"Game::~Game() initialized");
}

int Game::RunningGame(int argc, char** argv) {
    spdlog::info(u8"Game::RunningGame() initialized");
    (void)argc; 
    (void)argv;
    while (isRunning) {

    }
    return 0;
}
