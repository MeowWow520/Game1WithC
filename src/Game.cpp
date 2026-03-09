#include "Game.h"

Game::Game() {
    spdlog::info(u8"Game::Game() initialized");
}

Game::~Game() {
    spdlog::info(u8"Game::~Game() initialized");
    SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Game::RuningTheGame(int argc, char** argv) {
    spdlog::info(u8"Game::RuningTheGame() initialized");
    (void)argc; 
    (void)argv;
    // 进入游戏循环
    while (isRunning) {
        spdlog::info(u8"Game is running ...");
    }
    return 0;
}
