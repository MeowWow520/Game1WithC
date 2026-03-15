#include "Game.h"



Game::Game() {
    /** 
     * 设置 spdlog 的日志输出等级
     * 参数 trace debug info warn err critical off
     */
    spdlog::set_level(spdlog::level::info);
    spdlog::info(u8"Entering Game::Game()......");
}

Game::~Game() {
    spdlog::info(u8"Entering Game::~Game()......");
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
    spdlog::info(u8"Entering Game::Initialize()......");


    frameTime = 1000 / FPS;
    // 初始化 SDL 库
    spdlog::info(u8"[init] Initializing SDL_Init......");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error(u8"SDL_Init initialized failed");
    } else { spdlog::info(u8"[init] Initialized SDL_Init successfully"); };

    // 初始化 SDL_image 库
    spdlog::info(u8"[init] Initializing IMG_Init......");
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        spdlog::error(u8"IMG_Init initialized failed");
    } else { spdlog::info(u8"[init] Initialized IMG_Init successfully"); };

    // 初始化窗口
    spdlog::info(u8"[init] Initializing SDL_CreateWindow......");
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN );
	if (sdlWindow == nullptr) {
        spdlog::error(u8"SDL_CreateWindow initialized failed");
    } else { spdlog::info(u8"[init] Initialized SDL_CreateWindow successfully"); };

    // 初始化渲染器
    spdlog::info(u8"[init] Initializing SDL_CreateRenderer......");
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr) {
        spdlog::error(u8"[init] SDL_CreateRenderer initialized failed");
    } else { spdlog::info(u8"[init] Initialized SDL_CreateRenderer successfully"); };

    // 创建场景类
    spdlog::info(u8"[init] Creating new SceneMain......");
    currentScene = new SceneMain();
    // 初始化场景类
    currentScene->Initialize();
}

void Game::handleEvents(SDL_Event *event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            spdlog::info(u8"Received SDL_QUIT event, exiting game loop......");
            isRunning = false; }
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
    spdlog::info(u8"Entering Game::Clean()......");

    // 删除 SDL 资源
    // 删除渲染器
    try {
        SDL_DestroyRenderer(sdlRenderer);
        spdlog::info(u8"[Clean] Cleaned up SDL_Renderer");
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup SDL_Renderer: {}", e.what());
    }
    // 删除窗口
    try {
        SDL_DestroyWindow(sdlWindow);
        spdlog::info(u8"[Clean] Cleaned up SDL_Window");
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup SDL_Window: {}", e.what());
    }
    // 删除 SDL 图片库
    try {
        IMG_Quit();
        spdlog::info(u8"[Clean] Cleaned up IMG_Quit");
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup IMG_Quit: {}", e.what());
    }
    // 删除 SDL 库
    try {    
        SDL_Quit();
        spdlog::info(u8"[Clean] Cleaned up SDL_Quit");
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup SDL_Quit: {}", e.what());
    } 
    spdlog::info(u8"[Clean] SDL libraries cleaned up");

    // 删除场景资源
    if (currentScene != nullptr) {
        currentScene->Clean();
        delete currentScene;
        spdlog::info(u8"[Clean] Cleaned up currentScene");
    }
}

void Game::changeScene(Scene *scene) {
    spdlog::info(u8"Changing scene to {}......", typeid(*scene).name());
    if (currentScene != nullptr) {
        currentScene->Clean();
    }
    currentScene = scene;
    if (currentScene != nullptr) {
        spdlog::info(u8"[init] Initializing new scene {}......", typeid(*currentScene).name());
        currentScene->Initialize();
    } else spdlog::error(u8"New scene is nullptr, no scene to initialize");
}
