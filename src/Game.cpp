#include "Game.h"



Game::Game() {
    /** 
     * 设置 spdlog 的日志输出等级
     * 参数 trace debug info warn err critical off
     */
    spdlog::set_level(spdlog::level::info);
    spdlog::info(u8"Entering Game::Game()");
}

Game::~Game() {
    spdlog::info(u8"Entering Game::~Game()");
    // 执行 Game::Clean(); 删除 gameInstance 实例的初始化
    Clean();
}

int Game::RunningGame(int argc, char** argv) {
    spdlog::info(u8"Entering Game::RunningGame()");
    (void)argc, (void)argv;

    // 初始化
    Initialize();
    spdlog::info(u8"Entering main game loop");

    // 主循环
    while (isRunning) {
        SDL_Event event;
        handleEvents(&event);
        Update();
        Render();
    }
    spdlog::info(u8"Exited main game loop");

    spdlog::info(u8"Game.cpp --> Game::RunningGame() will return 0");
    return 0;
}

void Game::Initialize() { 
    spdlog::info(u8"Entering Game::Initialize()");
    
    // 初始化 SDL 库
    spdlog::info(u8"Initializing SDL_Init");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error(u8"SDL_Init initialized failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_Init successfully"); };

    // 初始化 SDL_image 库
    spdlog::info(u8"Initializing IMG_Init");
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        spdlog::error(u8"IMG_Init initialized failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized IMG_Init successfully"); };

    // 初始化窗口
    spdlog::info(u8"Initializing SDL_CreateWindow");
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN );
	if (sdlWindow == nullptr) {
        spdlog::error(u8"SDL_CreateWindow initialized failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_CreateWindow successfully"); };

    // 初始化渲染器
    spdlog::info(u8"Initializing SDL_CreateRenderer");
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr) {
        spdlog::error(u8"SDL_CreateRenderer initialized failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_CreateRenderer successfully"); };

    // 创建场景类
    currentScene = new SceneMain();
    spdlog::info(u8"currentScene = new SceneMain() called");
    // 初始化场景类
    currentScene->Initialize();
}

void Game::handleEvents(SDL_Event *event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            spdlog::info(u8"Received SDL_QUIT event, exiting game loop");
            isRunning = false;
        }
        currentScene->handleEvents(event);
    }
}

void Game::Update() { currentScene->Update(); }

void Game::Render() {
    SDL_RenderClear(sdlRenderer);
    currentScene->Render();
    SDL_RenderPresent(sdlRenderer);
}

void Game::Clean() {
    // 删除资源
    spdlog::info(u8"Entering Game::Clean()");

    // 删除 SDL 资源
    try {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        IMG_Quit();
        SDL_Quit();
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup: {}", e.what());
    }
    spdlog::info(u8"SDL libraries cleaned up");

    // 删除场景资源
    if (currentScene != nullptr) {
        currentScene->Clean();
        delete currentScene;
    }
}

void Game::changeScene(Scene *scene) {
    spdlog::info(u8"Changing scene to {}", typeid(*scene).name());
    if (currentScene != nullptr) {
        currentScene->Clean();
    }
    currentScene = scene;
    if (currentScene != nullptr) {
        spdlog::info(u8"Initializing new scene {}", typeid(*currentScene).name());
        currentScene->Initialize();
    } else spdlog::error(u8"New scene is nullptr, no scene to initialize");
}
