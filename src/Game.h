#pragma once

#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <spdlog/spdlog.h>
#include "Scene.h"


class Game {
public:
    Game() = default;
    ~Game() = default;
    void Run();
    void Init();
    void Update();
    void Clean();
    void SetCurrentScene(Scene* scene);

private:
    bool isRunning = true;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

#endif // !GAME_H