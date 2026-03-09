#pragma once 

#ifndef GAME_H
#define GAME_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "SingletonInstance.h"


class Game : public SITemplate<Game> {
    friend class SITemplate<Game>;
public:
    Game();
    ~Game();
    int RunningGame(int argc, char** argv);
    int temp = 0;

private:
    // Game Config Settings
    int windowWidth = 800;
    int windowHeight = 600;
    bool isRunning = true;

};

#endif // !GAME_H