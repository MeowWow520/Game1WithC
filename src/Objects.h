/**
 * 结构体变量的设计逻辑,适用于所有结构体
 * @param texture 纹理内容，用来在 SDL 库中初始化纹理
 * @param position 资源文件是一个透明背景的图片，图片的左上角在游戏中的坐标被存在这个变量中
 * @param speed 速度，用来管理对象的移动速度
 * @param width assets 图片的宽度，在后续的碰撞箱计算中会使用到
 * @param height assets 图片的高度，在后续的碰撞箱计算中会使用到
 * @param hitboxWidth 这是碰撞检测时用到的检测两个 Rect 是否重叠的那个图形的宽度。这一部分的值是我手动调整的
 * @param hitboxHeidth 这是碰撞检测时用到的检测两个 Rect 是否重叠的那个图形的宽度。这一部分的值是我手动调整的
 * @param edgeUP 这是 assets 图片显示的图形上方的空白像素行数。在检测资源是否超出显示区的时候会用到。类似的edgeDown等也是这个逻辑
 * @param zoom 缩放等级，用于调整资源文件渲染时显示的大小
 * @param currentHealth 当前的生命值
 * @param coolDown 用来存储射击的冷却时间，单位为 ms
 * @param lastShootTime 用来存储距离上次射击的时间
 */
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
    int zoom = 2;
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
    int zoom = 2;
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
    int zoom = 2;
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
    int zoom = 2;
    int damage = 1;

};

#endif // OBJECTS_H