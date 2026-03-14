#pragma once 

#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>



class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;
    virtual void Initialize() = 0;
    virtual void handleEvents(SDL_Event* event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Clean() = 0;
};
#endif // SCENE_H