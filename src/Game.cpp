#include "Game.h"



Game::Game() {
    spdlog::set_level(spdlog::level::info);
    spdlog::info(u8"Entering Game::Game()");
    Game::Initialize();
}

Game::~Game() {
    spdlog::info(u8"Entering Game::~Game()");
    Game::Clean();
}

bool Game::initSDLlibAssests(bool flags, const char* libName) {
    if (!flags) {
        spdlog::error(u8"{} Called Failed!", libName);
        return false;
    }
    spdlog::info(u8"{} Called Successfully!", libName);
    return true;
}

int Game::RunningGame(int argc, char** argv) {
    spdlog::info(u8"Entering Game::RunningGame()");
    (void)argc, (void)argv;


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
    initSDLlibAssests(SDL_Init(SDL_INIT_EVERYTHING) == 0, u8"SDL_Init");
    initSDLlibAssests(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0, u8"IMG_Init");
    initSDLlibAssests(TTF_Init() == 0, u8"TTF_Init");
    initSDLlibAssests(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != 0, u8"Mix_Init");

    // SDL Lib Settings
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN);
	initSDLlibAssests(sdlWindow != nullptr, u8"SDL Window");


    currentScene = new SceneMain();
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

void Game::Update() { }

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
        TTF_Quit();
        Mix_Quit();
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
        delete currentScene;
    }
    // currentScene = scene;
    currentScene->Initialize();
}
