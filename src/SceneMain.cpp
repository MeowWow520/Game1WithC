#include "SceneMain.h"
#include "Game.h"



// 引入 gameInstance
SceneMain::SceneMain() : gameInstance(Game::getInstance()) { }

SceneMain::~SceneMain() { }

void SceneMain::Initialize() {
    // 初始化随机数生成器
    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f);

    // 初始化玩家子弹模板
    projectilePlayerTemplate.texture = IMG_LoadTexture(
        gameInstance.getRenderer(), 
        u8"assets/Foozle_MainShip/Weapons/Projectile-Rocket-1.png"
    );
    if (projectilePlayerTemplate.texture != nullptr) {
        SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, 
                    &projectilePlayerTemplate.width, 
                    &projectilePlayerTemplate.height);
    } else { return; }
    projectilePlayerTemplate.width *= projectilePlayerTemplate.zoom;
    projectilePlayerTemplate.height *= projectilePlayerTemplate.zoom;

    // 初始化敌机子弹
    projectileEnemyTemplate.texture = IMG_LoadTexture(
        gameInstance.getRenderer(), 
        u8"assets/Foozle_MainShip/Weapons/Projectile-Rocket-1.png"
    );
    if (projectileEnemyTemplate.texture != nullptr) {
        SDL_QueryTexture(projectileEnemyTemplate.texture, NULL, NULL, 
                            &projectileEnemyTemplate.width, 
                            &projectileEnemyTemplate.height);
    } else { return; }
    projectileEnemyTemplate.width *= projectileEnemyTemplate.zoom;
    projectileEnemyTemplate.height *= projectileEnemyTemplate.zoom;

    // 初始化背景
    background.texture = IMG_LoadTexture(
        gameInstance.getRenderer(), 
        u8"assets/Backgrounds/orig.png"
    );
    if (background.texture != nullptr) {
        SDL_QueryTexture(background.texture, NULL, NULL, 
            &background.width, &background.height);
    }
    background.width *= background.zoom;
    background.height *= background.zoom;
    background.position.x = 0;
    background.position.y = 0;

    // 初始化玩家
    player.texture = IMG_LoadTexture(
        gameInstance.getRenderer(), 
        u8"assets/Foozle_MainShip/Bases/Full_health.png"
    );
    if (player.texture != nullptr) {
        SDL_QueryTexture(player.texture, NULL, NULL, 
            &player.width, &player.height);
    }
    // 设置玩家缩放比例 设置默认玩家位置
    player.width *= player.zoom;
    player.height *= player.zoom;
    player.position.x = (float)(gameInstance.getWindowWidth() / 2) - (float)(player.width / 2);
    player.position.y = (float)(gameInstance.getWindowHeight() - player.height);

    // 初始化敌机模板
    enemyTemplate.texture = IMG_LoadTexture(
        gameInstance.getRenderer(), 
        u8"assets/Foozle_MainShip/Engines/Base_Engine.png"
    );
    if (enemyTemplate.texture != nullptr) {
        SDL_QueryTexture(enemyTemplate.texture, NULL, NULL, 
            &enemyTemplate.width, &enemyTemplate.height);
    }
    // 设置敌机模板缩放比例
    enemyTemplate.width *= enemyTemplate.zoom;
    enemyTemplate.height *= enemyTemplate.zoom;
}

void SceneMain::handleEvents(SDL_Event *event) { return; }

void SceneMain::Update(float deltaTime) {
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
    updateEnemyProjectiles(deltaTime);
    spawEnemy();
    updateEnemies(deltaTime);
    updatePlayer(deltaTime);
}

void SceneMain::Render() {

    SDL_Rect backgroundRect = { static_cast<int>(background.position.x), 
                                static_cast<int>(background.position.y), 
                                background.width, 
                                background.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), background.texture, NULL, &backgroundRect) != 0)
        return;

    if (!isDead) {
        SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                                static_cast<int>(player.position.y), 
                                player.width,  player.height };
        if (SDL_RenderCopy(gameInstance.getRenderer(), player.texture, NULL, &playerRect) != 0)
            return;
    }
    renderPlayerProjectiles();
    renderEnemyProjectiles();
    renderEnemies();
}

void SceneMain::Clean() { 
    // 删除背景纹理
    if (background.texture != nullptr) 
        SDL_DestroyTexture(background.texture);
    
    // 删除玩家纹理
    if (player.texture != nullptr) 
        SDL_DestroyTexture(player.texture);

    // 删除玩家子弹
    for (auto &projectile : projectilesPlayer) {
        if (projectile != nullptr) delete projectile;
    }
    projectilesPlayer.clear();

    // 删除玩家子弹模板
    if (projectilePlayerTemplate.texture != nullptr)
        SDL_DestroyTexture(projectilePlayerTemplate.texture);

    // 删除敌机模板
    if (enemyTemplate.texture != nullptr) 
        SDL_DestroyTexture(enemyTemplate.texture);

    // 删除敌机
    for (auto &enemy : enemies) {
        if (enemy != nullptr) delete enemy;
    }
    enemies.clear();
    // 删除敌机子弹
    for (auto &projectile : projectilesEnemy) {
        if (projectile != nullptr) delete projectile;
    }
    projectilesEnemy.clear();

    // 删除敌人子弹模板
    if (projectileEnemyTemplate.texture != nullptr) 
        SDL_DestroyTexture(projectileEnemyTemplate.texture);

}


// 逻辑大概是对的了
void SceneMain::keyboardControl(float deltaTime) {
    auto keyboardState = SDL_GetKeyboardState(NULL);
    // 控制玩家移动
    if (keyboardState[SDL_SCANCODE_W]) {
        if (player.position.y > - player.edgeUP * player.zoom)
            player.position.y -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        if (player.position.y < gameInstance.getWindowHeight() - 
                                (player.height - player.edgeDown ) * player.zoom)
            player.position.y += deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        if (player.position.x > - player.edgeLeft * player.zoom )
            player.position.x -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        if (player.position.x < gameInstance.getWindowWidth() - 
                                (player.width - player.edgeRight) * player.zoom)
            player.position.x += deltaTime * player.speed;
    }
    // 控制子弹发射
    if (keyboardState[SDL_SCANCODE_E]) {
        auto currentTime = SDL_GetTicks();
        if (currentTime - player.lastShootTime >= player.coolDown) {
            shootPlayer();
            player.lastShootTime = currentTime;
        }
    }
}

// 逻辑大概是对的了
void SceneMain::shootPlayer() {
    // 创建新子弹
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    // 定位在碰撞箱顶部中央
    projectile->position.x = player.position.x + 
                             player.width / 2 * player.zoom -
                             projectile->width / 2 * projectile->zoom;
    projectile->position.y = player.position.y + (player.height - player.hitboxHeight) / 2 * player.zoom;
    // 添加到活动子弹列表
    projectilesPlayer.push_back(projectile);
}

// 逻辑大概是对的了
void SceneMain::updatePlayerProjectiles(float deltaTime) {
    int margin = 32;
    for (auto it = projectilesPlayer.begin(); it != projectilesPlayer.end();) {
        auto projectile = *it;
        // 更新子弹位置
        projectile->position.y -= projectile->speed * deltaTime;
        // 检查子弹是否超出屏幕
        if (projectile->position.y  < - projectile->height * projectile->zoom - margin) {
            delete projectile;
            it = projectilesPlayer.erase(it);
        } else {
            bool hit = false;
            for (auto enemy : enemies) {
                // 敌人的碰撞箱图形的左上角 xy 坐标
                int enemyRectPosX = enemy->position.x + (enemy->width - enemy->hitboxWidth / 2 ) * enemy->zoom;
                int enemyRextPosY = enemy->position.y + (enemy->height - enemy->hitboxHeight) / 2 * enemy->zoom;
                SDL_Rect enemyRect = {
                    static_cast<int>(enemyRectPosX),
                    static_cast<int>(enemyRextPosY),
                    enemy->hitboxWidth, enemy->hitboxHeight
                };
                // 玩家子弹的碰撞箱图形的左上角 xy 坐标
                int projectileRectPosX = (
                    projectile->position.x + (projectile->width - projectile->hitboxWidth / 2 ) * projectile->zoom
                );
                int projectileRectPosY = (
                    projectile->position.y + (projectile->height - projectile->hitboxHeight / 2 ) * projectile->zoom
                );
                SDL_Rect projectileRect = {
                    static_cast<int>(projectileRectPosX),
                    static_cast<int>(projectileRectPosY),
                    projectile->hitboxWidth, projectile->hitboxHeight };
                
                    if (SDL_HasIntersection(&enemyRect, &projectileRect)) {
                        enemy->currentHealth -= projectile->damage;
                        hit = true;
                        delete projectile;
                        it = projectilesPlayer.erase(it);
                        break; 
                    }
            }
            if (!hit) { ++it; }
        }
    }
}

void SceneMain::renderPlayerProjectiles() {
    for (auto projectile : projectilesPlayer) {
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width, projectile->height };
        if (SDL_RenderCopy(gameInstance.getRenderer(), projectile->texture, NULL, &projectileRect) != 0)
            return;
    }
}

void SceneMain::spawEnemy() {
    if (dis(gen) > 1 / 60.0f) return;
    Enemy* enemy = new Enemy(enemyTemplate);
    enemy->position.x = dis(gen) * (gameInstance.getWindowWidth() - enemy->width);
    enemy->position.y = (float)(- enemy->height);
    enemies.push_back(enemy);
}

void SceneMain::renderEnemies() {
    for (auto enemy : enemies) {
        SDL_Rect enemyRect = {
            static_cast<int>(enemy->position.x),
            static_cast<int>(enemy->position.y),
            enemy->width,
            enemy->height };
        if (SDL_RenderCopyEx(gameInstance.getRenderer(), 
                             enemy->texture, NULL, 
                             &enemyRect, 180.00f, NULL, SDL_FLIP_NONE) != 0
        ) return;
    }
}

void SceneMain::shootEnemy(Enemy *enemy) {

    auto projectile = new ProjectileEnemy(projectileEnemyTemplate);
    projectile->position.x = enemy->position.x + (enemy->width * enemy->zoom- projectile->width * projectile->zoom) / 2 ;
    projectile->position.y = enemy->position.y + enemy->height / 2 - projectile->height / 2;
    projectile->direction = getDirection(enemy);
    projectilesEnemy.push_back(projectile);

}

// 逻辑大概是对的了
void SceneMain::updatePlayer(float deltaTime) {

    if (isDead) return;
    if (player.currentHealth <= 0) isDead = true;
    for (auto enemy : enemies) {
        // 敌人的碰撞箱图形的左上角 xy 坐标
        int enemyRectPosX = enemy->position.x + (enemy->width - enemy->hitboxWidth / 2 ) * enemy->zoom;
        int enemyRextPosY = enemy->position.y + (enemy->height - enemy->hitboxHeight) / 2 * enemy->zoom;
        SDL_Rect enemyRect = {
            static_cast<int>(enemyRectPosX),
            static_cast<int>(enemyRextPosY),
            enemy->hitboxWidth, enemy->hitboxHeight };
        // 玩家的碰撞箱图形的左上角 xy 坐标
        int playerRectPosX = player.position.x + (player.width - player.hitboxWidth) / 2 * player.zoom;
        int playerRectPosY = player.position.y + (player.height - player.hitboxHeight) / 2 * player.zoom;
        SDL_Rect playerRect = {
            static_cast<int>(playerRectPosX),
            static_cast<int>(playerRectPosY),
            player.hitboxWidth, player.hitboxHeight };
        if (SDL_HasIntersection(&playerRect, &enemyRect)) { 
            player.currentHealth -= 1;
            enemy->currentHealth = 0;
        }
    }

}

void SceneMain::enemyExplode(Enemy *enemy) { delete enemy; }

void SceneMain::updateEnemies(float deltaTime) {

    auto currentTime = SDL_GetTicks();
    for (auto it = enemies.begin(); it != enemies.end();) {
        auto enemy = *it;
        enemy->position.y += enemy->speed * deltaTime;
        if (enemy->position.y > gameInstance.getWindowHeight()) {
            delete enemy;
            it = enemies.erase(it);
        } else {
            if (currentTime - enemy->lastShootTime > enemy->coolDown) {
                shootEnemy(enemy);
                enemy->lastShootTime = currentTime;
            }
            if (enemy->currentHealth <= 0) {
                enemyExplode(enemy);
                it = enemies.erase(it);
            } else { ++it; }
        }
    }

}

void SceneMain::updateEnemyProjectiles(float deltaTime) {

    auto margin = 64;
    for (auto it = projectilesEnemy.begin(); it != projectilesEnemy.end();) {
        auto projectile = *it;
        projectile->position.x += projectile->speed * projectile->direction.x * deltaTime;
        projectile->position.y += projectile->speed * projectile->direction.y * deltaTime;
        if (projectile->position.y > gameInstance.getWindowHeight() + margin ||
            projectile->position.y < - margin ||
            projectile->position.x < - margin ||
            projectile->position.x > gameInstance.getWindowWidth() + margin) {
            delete projectile;
            it = projectilesEnemy.erase(it);
        } else {
            // 敌人子弹的碰撞箱图形的左上角 xy 坐标
            int projectileRectPosX = projectile->position.x + (projectile->width - projectile->hitboxWidth / 2 ) * projectile->zoom;
            int projectileRectPosY = projectile->position.y + (projectile->height - projectile->hitboxHeight) / 2 * projectile->zoom;
            SDL_Rect projectileRect = {
                static_cast<int>(projectileRectPosX),
                static_cast<int>(projectileRectPosY),
                projectile->hitboxWidth, projectile->hitboxHeight };
            // 玩家的碰撞箱图形的左上角 xy 坐标
            int playerRectPosX = player.position.x + (player.width - player.hitboxWidth) / 2 * player.zoom;
            int playerRectPosY = player.position.y + (player.height - player.hitboxHeight) / 2 * player.zoom;
            SDL_Rect playerRect = {
                static_cast<int>(playerRectPosX),
                static_cast<int>(playerRectPosY),
                player.hitboxWidth, player.hitboxHeight };
            if (SDL_HasIntersection(&projectileRect, &playerRect) && !isDead){
                player.currentHealth -= projectile->damage;
                delete projectile;
                it = projectilesEnemy.erase(it);
            } else { ++it; }
        }

    }

}

void SceneMain::renderEnemyProjectiles() {

    for (auto projectile : projectilesEnemy) {
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width, projectile->height };
        float angle = atan2(projectile->direction.y, projectile->direction.x) * 180 / (float)M_PI + 90;
        SDL_RenderCopyEx(gameInstance.getRenderer(), projectile->texture, NULL, &projectileRect, angle, NULL, SDL_FLIP_NONE);
    }

}

SDL_FPoint SceneMain::getDirection(Enemy *enemy) {

    auto x = (player.position.x + player.width / 2) - (enemy->position.x + enemy->width / 2);
    auto y = (player.position.y + player.height / 2) - (enemy->position.y + enemy->height / 2);
    auto length = sqrt(x * x + y * y);
    x /= length;
    y /= length;
    return SDL_FPoint{x, y};

}
