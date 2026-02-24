#pragma once

#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>


class Scene {
public:
    Scene() = default;
    ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Clean() = 0;
    virtual void HandleEvents(SDL_Event* event) = 0;
};
#endif // !SCENE_H