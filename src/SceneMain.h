#pragma once

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "Scene.h"
#include "Objects.h"


// 声明 Game 类，防止在 include 的时候循环引入
/**
 * 编译器：请输入文本
 * Game.h #include "Scene.h" 
 * SceneMain.h #include "Game.h"
 */
class Game;

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void Initialize() override;
    void handleEvents(SDL_Event* event) override;
    void Update() override;
    void Render() override;
    void Clean() override;
private:
    // 在 SceneMain.h 里调用 gameInstance 实例的引用
    Game& gameInstance;
    // 玩家实例
    Player player;
};

#endif // SCENEMAIN_H