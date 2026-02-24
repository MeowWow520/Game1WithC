#pragma once

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include <SDL.h>
#include "Scene.h"


class SceneMain : public Scene {
public:
    void Init() override;
    void Update() override;
    void Render() override;
    void Clean() override;
    void HandleEvents(SDL_Event* event) override;

};

#endif // !SCENEMAIN_H