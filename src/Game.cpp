#include "Game.h"

Game::Game() {
    spdlog::set_level(spdlog::level::info);
    spdlog::info(u8"Entering Game::Game()");

    // Initialize SDL
    initAssests(SDL_Init(SDL_INIT_EVERYTHING) == 0, u8"SDL_Init");
    initAssests(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0, u8"IMG_Init");
    initAssests(TTF_Init() == 0, u8"TTF_Init");
    initAssests(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != 0, u8"Mix_Init");

    // SDL Lib Settings
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    sdlWindow = SDL_CreateWindow(windowTitle, 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			windowWidth, windowHeight, 
			SDL_WINDOW_SHOWN);
	initAssests(sdlWindow != nullptr, u8"SDL Window");
}

Game::~Game() {
    spdlog::info(u8"Entering Game::~Game()");
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::initAssests(bool flags, const char* libName) {
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
        std::cin >> isRunning;
    }
    spdlog::info(u8"Exited main game loop");
    return 0;
}

void Game::init()
{
}

void Game::handleEvents()
{
}

void Game::update()
{
}

void Game::render()
{
}
