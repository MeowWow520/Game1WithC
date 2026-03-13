#pragma once

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include <SDL.h>
#include "Scene.h"



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

};

#endif // SCENEMAIN_H