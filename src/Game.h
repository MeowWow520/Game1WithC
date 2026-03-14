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
 * @param windowWidth 窗口宽度
 * @param windowHeight 窗口高度
 * @param windowTitle 窗口标题
 * @param isRunning 主循环布尔值
 */
class Game {

public:
    Game();
    ~Game();

    /**
     * 主循环所在函数
     * @param argc main 函数的 int argc 值
     * @param argv main 函数的 char** argv 值
     * @return 返回 0 以表示成功 
     */
    int RunningGame(int argc, char** argv);

    // 初始化 main 函数资源，如窗口创建，字体设置etc.
    void Initialize();

    // 主循环处理事件，负责正常关闭窗口
    void handleEvents(SDL_Event *event);

    // Update() 调用 currentScene 实例的更新函数，更新数据
    void Update(float deltaTime);

    // 渲染
    void Render();

    // 清理资源
    void Clean();

    /**
     * 改变当前场景
     * @param scene 改变的场景指针
     */
    void changeScene(Scene* scene);

    // 单例模式实现
    static Game& getInstance() {
        static Game instance;
        return instance;
    }


    // 获取 SDL_Renderer 的静态方法
    static SDL_Renderer* getRenderer() { return getInstance().sdlRenderer; }

    // 获取 windowWidth 的静态方法
    static int getWindowWidth() { return getInstance().windowWidth; }

    // 获取 windowHeight 的静态方法
    static int getWindowHeight() { return getInstance().windowHeight; }

private:

    //禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator = (const Game&) = delete;

    // 游戏参数设置
    // 窗口宽度
    int windowWidth = 1960;

    // 窗口高度
    int windowHeight = 1080;

    // 窗口标题
    char windowTitle[256] = u8"Game1 With C";

    // 主循环布尔值
    bool isRunning = true;

    // 每秒帧率
    int FPS = 60;

    // 每帧间隔时间
    Uint32 frameTime;
    float deltaTime; 

    // SDL 库的变量
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    Scene* currentScene = nullptr;
};

#endif // !GAME_H