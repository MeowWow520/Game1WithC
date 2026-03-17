#pragma once 

#ifndef OBJECTS_H
#define OBJECTS_H
#include <SDL.h>



struct Player {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    int speed = 800;
    int width = 0;
    int height = 0;
    int hitboxWidth = 12;
    int hitboxHeight = 26;
    int edgeUP = 11;
    int edgeDown = 11;
    int edgeLeft = 9;
    int edgeRight = 9;
    int zoom = 1;
    int currentHealth = 20;
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
    int speed = 400;
    int width = 0;
    int height = 0;
    int hitboxWidth = 6;
    int hitboxHeight = 16;
    int zoom = 1;
    int damage = 1;

};

struct Enemy {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0, 0};
    int speed = 200;
    int width = 0;
    int height = 0; // 6 * 8
    int hitboxWidth = 12;
    int hitboxHeight = 15;
    int edgeUP = 20;
    int edgeDown = 13;
    int edgeLeft = 13;
    int edgeRight = 13;
    int zoom = 1;
    int currentHealth = 1;
    Uint32 coolDown = 1000;
    Uint32 lastShootTime = 0;

};

struct ProjectileEnemy {

    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.00f, 0.00f};
    SDL_FPoint direction = {0, 0};
    int speed = 200;
    int width = 0;
    int height = 0;
    int hitboxWidth = 6;
    int hitboxHeight = 16;
    int zoom = 1;
    int damage = 1;

};

#endif // OBJECTS_H