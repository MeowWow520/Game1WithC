#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include "Game.h"



int main(int argc, char** argv) 
{
    spdlog::info(u8"Main.cpp initialized");
    return Game::Instance()->RuningTheGame(argc, argv);
}