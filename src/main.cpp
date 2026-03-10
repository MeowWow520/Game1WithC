#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include "Game.h"


#ifdef _WIN32
#include <Windows.h>
#endif

void setup_console() {
#ifdef _WIN32
    // 设置控制台输出代码页为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // 可选：如果需要从控制台读取中文，也设置输入代码页
    SetConsoleCP(CP_UTF8);
    spdlog::info(u8"Console code page set to UTF-8");
#endif
    return;
}


int main(int argc, char** argv) {
    setup_console();
    spdlog::info(u8"Entering main()");
    
    spdlog::info(u8"Created Game instance");
    Game& gameInstance = Game::getInstance();
    return gameInstance.RunningGame(argc, argv);
}