#include "Game.h"



Game::Game() {
    spdlog::set_level(spdlog::level::info);
    spdlog::info(u8"Entering Game::Game()");
}

Game::~Game() {
    spdlog::info(u8"Entering Game::~Game()");
    Clean();
}

int Game::RunningGame(int argc, char** argv) {
    spdlog::info(u8"Entering Game::RunningGame()");
    (void)argc, (void)argv;


    Initialize();
    spdlog::info(u8"Entering main game loop");
    while (isRunning) {
        SDL_Event event;
        handleEvents(&event);
        Update();
        Render();
    }
    spdlog::info(u8"Exited main game loop");


    return 0;
}

void Game::Initialize() { 
    spdlog::info(u8"Entering Game::Initialize()");
    

    // Initialize SDL
    spdlog::info(u8"Initializing SDL_Init");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error(u8"SDL_Init Initialized Failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_Init Successfully"); };

    spdlog::info(u8"Initializing IMG_Init");
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        spdlog::error(u8"IMG_Init Initialized Failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized IMG_Init Successfully"); };

    spdlog::info(u8"Initializing SDL_CreateWindow");
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN );
	if (sdlWindow == nullptr) {
        spdlog::error(u8"SDL_CreateWindow Initialized Failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_CreateWindow Successfully"); };

    spdlog::info(u8"Initializing SDL_CreateRenderer");
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr) {
        spdlog::error(u8"SDL_CreateRenderer Initialized Failed");
        isRunning = false;
    } else { spdlog::info(u8"Initialized SDL_CreateRenderer Successfully"); };


    currentScene = new SceneMain();
    spdlog::info(u8"currentScene = new SceneMain() Called");
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
    // 清空
    SDL_RenderClear(sdlRenderer);
    currentScene->Render();
    // 显示更新
    SDL_RenderPresent(sdlRenderer);

}

void Game::Clean() {
    spdlog::info(u8"Entering Game::Clean()");


    try {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        IMG_Quit();
        SDL_Quit();
    } catch (const std::exception& e) {
        spdlog::error(u8"Exception during cleanup: {}", e.what());
    }
    spdlog::info(u8"SDL libraries cleaned up");

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
