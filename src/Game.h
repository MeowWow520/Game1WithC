#pragma once 

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "SceneMain.h"


/**
 * class Game 是游戏的主循环管理器
 */
class Game {

public:
    Game();
    ~Game();

    
    int RunningGame(int argc, char** argv);
    void Initialize();
    void handleEvents(SDL_Event *event);
    void Update(float deltaTime);
    void Render();
    void Clean();
    void changeScene(Scene* scene);

    // 单例模式实现
    static Game& getInstance() {
        static Game instance;
        return instance; }
    static SDL_Renderer* getRenderer() { return getInstance().sdlRenderer; }
    static int getWindowWidth() { return getInstance().windowWidth; }
    static int getWindowHeight() { return getInstance().windowHeight; }

private:

    //禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator = (const Game&) = delete;

    // 游戏参数设置
    int windowWidth = 600;
    int windowHeight = 950;
    char windowTitle[256] = u8"Game1 With C";
    bool isRunning = true;
    int FPS = 60;
    Uint32 frameTime;
    float deltaTime; 
    int isDead = false;

    // SDL 库的变量
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    Scene* currentScene = nullptr;
};

#endif // !GAME_H