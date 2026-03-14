#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include "Game.h"



int main(int argc, char** argv) {
    spdlog::info(u8"Entering main.cpp -> main function");
    spdlog::info(u8"There is branch main");
    
    spdlog::info(u8"Created Game instance");
    Game& gameInstance = Game::getInstance();
    return gameInstance.RunningGame(argc, argv);
}