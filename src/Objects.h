#pragma once 

#ifndef OBJECTS_H
#define OBJECTS_H
#include <SDL.h>



struct Player {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    int width = 0;
    int height = 0;
    int speed = 800;
    int edgeUP = 10;
    int edgeDown = 10;
    int edgeLeft = 8;
    int edgeRight = 8;
    int zoom = 2;
    int deviation = 2;
    int deviationZoom = 2;
    int currentHealth = 4;
    Uint32 coolDown = 1000;
    Uint32 lastShootTime = 0;

};

struct Background {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    int width = 0;
    int height = 0;
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
    int edgeUP = 9;
    int edgeDown = 9;
    int edgeLeft = 12;
    int edgeRight = 12;
    int zoom = 2;
    int deviation = 1;
    int deviationZoom = 1;
    int damage = 1;

};

struct Enemy {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 200;
    int edgeUP = 10;
    int edgeDown = 10;
    int edgeLeft = 8;
    int edgeRight = 8;
    int zoom = 2;
    int deviation = 2;
    int deviationZoom = 2;
    int currentHealth = 4;
    Uint32 coolDown = 1000;
    Uint32 lastShootTime = 0;

};

struct ProjectileEnemy {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    SDL_FPoint direction = {0, 0};
    int width = 0;
    int height = 0;
    int speed = 200;
    int edgeUP = 25;
    int edgeDown = 7;
    int edgeLeft = 18;
    int edgeRight = 18;
    int zoom = 2;
    int deviation = 0;
    int deviationZoom = 0;
    int damage = 1;

};

#endif // OBJECTS_H