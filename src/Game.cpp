#include "Game.h"

void Game::Run() {
    while (isRunning) {
        SDL_Event event;
        currentScene->HandleEvents(&event);
        currentScene->Update();
        currentScene->Render();
    }
}

void Game::Init() {
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error("SDL 初始化失败: {}", SDL_GetError());
        isRunning = false;
    }
}

void Game::Update()
{
}

void Game::Clean()
{
}

void Game::SetCurrentScene(Scene *scene) {
    if (currentScene != nullptr) {
        currentScene->Clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->Init();
}
