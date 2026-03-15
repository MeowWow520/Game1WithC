#pragma once 

#ifndef OBJECTS_H
#define OBJECTS_H
#include <SDL.h>



struct Player {

    // 玩家的“材质”
    SDL_Texture* texture = nullptr;
    // 玩家位置的值
    SDL_FPoint position = {0.00f, 0.00f};
    // 玩家宽度 & 高度
    int width = 0;
    int height = 0;
    // 玩家速度
    int speed = 800;
    // 图片边框像素 偏移像素
    int edgeUP = 10;
    int edgeDown = 10;
    int edgeLeft = 8;
    int edgeRight = 8;
    int zoom = 2;
    int deviation = 2;
    int deviationZoom = 2;
    // 玩家血量
    int health = 4;
    Uint32 coolDown = 1000;
    Uint32 lastShootTime = 0;

};

struct Background {

    // 背景的“材质”
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    // 背景宽度 & 高度
    int width = 0;
    int height = 0;
    // 图片边框像素
    int edgeUP = 10;
    int edgeDown = 10;
    int edgeLeft = 8;
    int edgeRight = 8;
    int zoom = 3;

};

struct ProjectilePlayer {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    int width = 0;
    int height = 0;
    int speed = 400;
    // 图片边框像素 偏移像素
    int edgeUP = 9;
    int edgeDown = 9;
    int edgeLeft = 12;
    int edgeRight = 12;
    int zoom = 2;
    int deviation = 1;
    int deviationZoom = 1;

};

#endif // OBJECTS_H