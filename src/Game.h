#pragma once 

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <spdlog/spdlog.h>
#include "SceneMain.h"



class Game {

public:
    Game();
    ~Game();
    int RunningGame(int argc, char** argv);
    void Initialize();
    void handleEvents(SDL_Event *event);
    void Update();
    void Render();
    void Clean();
    /**
     * Change the current scene
     * @param scene The scene to change to
     */
    void changeScene(Scene* scene);

    // 单例模式实现
    static Game& getInstance() {
        static Game instance;
        return instance;
    }
    // 获取 SDL_Renderer 的静态方法
    static SDL_Renderer* getRenderer() { return getInstance().sdlRenderer; }
    static int getWindowWidth() { return getInstance().windowWidth; }
    static int getWindowHeight() { return getInstance().windowHeight; }
    /**
     * Initialize assets
     * @param flags Initialization flags, recieve true for normal functions
     * @param libName Library name
     * @return return true if initialization is successful, false otherwise
     */
    bool initSDLlibAssests(bool flags, const char* libName);

private:

    //禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator = (const Game&) = delete;

    // Game Config Settings
    int windowWidth = 1960;
    int windowHeight = 1080;
    char windowTitle[256] = u8"Game1 With C";
    bool isRunning = true;

    // SDL About Variables
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    Scene *currentScene = nullptr;

};

#endif // !GAME_H