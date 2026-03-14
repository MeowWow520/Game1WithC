#pragma once 

#ifndef OBJECTS_H
#define OBJECTS_H
#include <SDL.h>



struct Player
{
    // 玩家的“材质”
    SDL_Texture* texture = nullptr;
    // 玩家位置的值
    SDL_FPoint position = {0.00f, 0.00f};
    // 玩家宽度
    int width = 0;
    // 玩家高度
    int height = 0;
};

#endif // OBJECTS_H