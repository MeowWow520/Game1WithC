#pragma once 

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>


class Game {

public:
    Game();
    ~Game();
    int RunningGame(int argc, char** argv);
    void init();
    void handleEvents();
    void update();
    void render();
    // 单例模式实现
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

protected:
    /**
     * Initialize assets
     * @param flags Initialization flags, recieve true for normal functions
     * @param libName Library name
     * @return return true if initialization is successful, false otherwise
     */
    bool initAssests(bool flags, const char* libName);

private:

    //禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator = (const Game&) = delete;

    // Game Config Settings
    int windowWidth = 1960;
    int windowHeight = 1080;
    const char* windowTitle = u8"Game1 With C";
    bool isRunning = true;

    // SDL About Variables
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    SDL_Event sdlEvent;

};

#endif // !GAME_H