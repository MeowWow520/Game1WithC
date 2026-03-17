#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include "Game.h"



int main(int argc, char** argv) 
{
    // 创建 gameInstance 实例
    Game& gameInstance = Game::getInstance();
    // 执行 Game::RunningGame，将 int 类型的函数返回到 main
    return gameInstance.RunningGame(argc, argv);
}