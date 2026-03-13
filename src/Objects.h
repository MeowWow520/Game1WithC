#pragma once 

#ifndef OBJECTS_H
#define OBJECTS_H
#include <SDL.h>



struct Player
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    int width = 0;
    int height = 0;
};

#endif // OBJECTS_H