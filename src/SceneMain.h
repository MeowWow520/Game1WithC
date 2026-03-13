#pragma once

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "Scene.h"
#include "Objects.h"



class Game;

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void Initialize() override;
    void handleEvents(SDL_Event* event) override;
    void Update() override;
    void Render() override;
    void Clean() override;
private:
    Game& gameInstance;
    Player player;
};

#endif // SCENEMAIN_H