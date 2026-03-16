#pragma once

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include <list>
#include <random>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include "Scene.h"
#include "Objects.h"


// 声明 Game 类，防止在 include 的时候循环引入
/**
 * 编译器：请输入文本
 * Game.h #include "Scene.h" 
 * SceneMain.h #include "Game.h"
 */
class Game;

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void Initialize() override;
    void handleEvents(SDL_Event* event) override;
    void Update(float deltaTime) override;
    void Render() override;
    void Clean() override;

    void keyboardControl(float deltaTime);
    void shootPlayer();
    void updatePlayerProjectiles(float deltaTime);
    void renderPlayerProjectiles();
    void spawEnemy();
    void updateEnemies(float deltaTime);
    void updateEnemyProjectiles(float deltaTime);
    void renderEnemies();
    void renderEnemyProjectiles();
    void shootEnemy(Enemy* enemy);
    void updatePlayer(float deltaTime);
    void enemyExplode(Enemy* enemy);

    SDL_FPoint getDirection(Enemy* enemy); 
    
private:
    // 在 SceneMain.h 里调用 gameInstance 实例的引用
    Game& gameInstance;
    // 玩家实例
    Player player;
    Background background;

    // 创建模板
    ProjectilePlayer projectilePlayerTemplate;
    ProjectileEnemy projectileEnemyTemplate;
    Enemy enemyTemplate;

    // 玩家子弹和敌人子弹
    std::list<ProjectilePlayer*> projectilesPlayer;  
    std::list<ProjectileEnemy*> projectilesEnemy;
    std::list<Enemy*> enemies;

    // 随机数相关成员
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;

    bool isDead = false;
};


#endif // SCENEMAIN_H