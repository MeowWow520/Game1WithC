#include "Game.h"



Game::Game() {
    /** 
     * 设置 spdlog 的日志输出等级
     * 参数 trace debug info warn err critical off
     */
    spdlog::set_level(spdlog::level::info);
}

Game::~Game() {
    // 执行 Game::Clean(); 删除 gameInstance 实例的初始化
    Clean();
}

int Game::RunningGame(int argc, char** argv) {
    (void)argc, (void)argv;

    // 初始化
    Initialize();

    // 主循环
    while (isRunning) {

        auto frameStart = SDL_GetTicks();

        SDL_Event event;
        handleEvents(&event);
        Update(deltaTime);
        Render();

        auto frameEnd = SDL_GetTicks();  
        auto diff = frameEnd - frameStart;
        // 限制“帧率”
        if (diff < frameTime) {
            SDL_Delay(frameTime - diff);  
            deltaTime = frameTime / 1000.0f;  
        } else { deltaTime = diff / 1000.0f; }
    }
    return 0;
}

void Game::Initialize() { 
    frameTime = 1000 / FPS;
    // 初始化 SDL 库
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { return; }

    // 初始化 SDL_image 库
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) { return; }

    // 初始化窗口
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN );
	if (sdlWindow == nullptr) { return; }

    // 初始化渲染器
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr) { return; }

    // 创建场景类
    currentScene = new SceneMain();
    // 初始化场景类
    currentScene->Initialize();
}

void Game::handleEvents(SDL_Event *event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) { isRunning = false; }
        currentScene->handleEvents(event);
    }
}

void Game::Update(float deltaTime) { currentScene->Update(deltaTime); }

void Game::Render() {
    SDL_RenderClear(sdlRenderer);
    currentScene->Render();
    SDL_RenderPresent(sdlRenderer);
}

void Game::Clean() {
    // 删除 SDL 资源
    // 删除渲染器
    SDL_DestroyRenderer(sdlRenderer);
    // 删除窗口
    SDL_DestroyWindow(sdlWindow);
    // 删除 SDL 图片库
    IMG_Quit();
    // 删除 SDL 库
    SDL_Quit();
    // 删除场景资源
    if (currentScene != nullptr) {
        currentScene->Clean();
        delete currentScene;
    }
}

void Game::changeScene(Scene *scene) {
    if (currentScene != nullptr) { currentScene->Clean(); }
    currentScene = scene;
    if (currentScene != nullptr) { currentScene->Initialize(); } 
}
