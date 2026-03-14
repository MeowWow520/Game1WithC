#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <iostream>
#include <spdlog/spdlog.h>
#include "Game.h"



#ifdef _WIN32
#include <Windows.h>
#endif

// 在 Win32 平台下改变 Console 输出编码
void setup_console() {
#ifdef _WIN32
    // 设置控制台输出代码页为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // 如果需要从控制台读取中文，也设置输入代码页
    SetConsoleCP(CP_UTF8);
    spdlog::info(u8"Console code page set to UTF-8");
#endif
    return;
}



int main(int argc, char** argv) {
    // setup_console();
    spdlog::info(u8"There is branch main");
    spdlog::info(u8"main.cpp -> Entering main function");

    spdlog::info(u8"Created gameInstance instance");
    // 创建 gameInstance 实例
    Game& gameInstance = Game::getInstance();
    spdlog::info(u8"main.cpp --> Entering return");
    // 执行 Game::RunningGame，将 int 类型的函数返回到 main
    return gameInstance.RunningGame(argc, argv);
}