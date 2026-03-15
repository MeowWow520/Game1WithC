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
    // 玩家速度
    int speed = 1000;
    // 图片边框像素
    int edgeUP = 10;
    int edgeDown = 10;
    int edgeLeft = 8;
    int edgeRight = 8;
    int zoom = 3;
    // 玩家血量
    int health = 4;
};

#endif // OBJECTS_H