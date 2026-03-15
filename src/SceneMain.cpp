#include "SceneMain.h"
#include "Game.h"


// 引入 gameInstance
SceneMain::SceneMain() : gameInstance(Game::getInstance()) {
    spdlog::info(u8"Entering SceneMain::SceneMain()......");
}

SceneMain::~SceneMain() { 
    spdlog::info(u8"Entering SceneMain::~SceneMain()......");
}

void SceneMain::Initialize() {
    spdlog::info(u8"Entering SceneMain::Initialize()......");

    // 初始化子弹模板
    spdlog::info(u8"[init] Initializing projectilePlayerTemplate texture......");
    projectilePlayerTemplate.texture = IMG_LoadTexture(gameInstance.getRenderer(), u8"assets/Foozle_MainShip/Main ship weapons/Main ship weapon - Projectile - Rocket - 1.png");
    if (projectilePlayerTemplate.texture == nullptr) {
        spdlog::error(u8"Failed to load projectilePlayerTemplate texture: {}", SDL_GetError());
    } else {         
        spdlog::info(u8"[init] background.texture loaded successfully");
        SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, 
                            &projectilePlayerTemplate.width, 
                            &projectilePlayerTemplate.height); 
        spdlog::info(u8"[init] projectilePlayerTemplate called SDL_QueryTexture()");
    }
    projectilePlayerTemplate.width *= projectilePlayerTemplate.zoom;
    projectilePlayerTemplate.height *= projectilePlayerTemplate.zoom;


    // 初始化背景
    spdlog::info(u8"[init] Initializing background texture......");
    background.texture = IMG_LoadTexture(gameInstance.getRenderer(), u8"assets/Backgrounds/orig.png");
    if (background.texture == nullptr) {
              spdlog::error(u8"Failed to load background texture: {}", SDL_GetError());
    } else { 
        spdlog::info(u8"[init] background.texture loaded successfully");
        SDL_QueryTexture(background.texture, NULL, NULL, &background.width, &background.height);
        spdlog::info(u8"[init] background called SDL_QueryTexture()");
    }
    // 设置背景缩放比例 设置默认背景位置
    background.width *= background.zoom;
    background.height *= background.zoom;
    background.position.x = 0;
    background.position.y = 0;

    // 初始化玩家
    spdlog::info(u8"[init] Initializing player.texture......");
    player.texture = IMG_LoadTexture(gameInstance.getRenderer(), u8"assets/Foozle_MainShip/Main Ship - Bases/Main Ship - Base - Full health.png");
    if (player.texture == nullptr) {
        spdlog::error(u8"Failed to load player texture: {}", SDL_GetError());
    } else { 
        spdlog::info(u8"[init] Player.texture loaded successfully");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
        spdlog::info(u8"[init] player called SDL_QueryTexture()");
    }
    // 设置玩家缩放比例 设置默认玩家位置
    player.width *= player.zoom;
    player.height *= player.zoom;
    player.position.x = (float)(gameInstance.getWindowWidth() / 2) - (float)(player.width / 2);
    player.position.y = (float)(gameInstance.getWindowHeight() - player.height);
}

void SceneMain::handleEvents(SDL_Event *event) { return; }

void SceneMain::Update(float deltaTime) {
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
}

void SceneMain::Render() {
    // 渲染背景
    SDL_Rect backgroundRect = { static_cast<int>(background.position.x), 
                                static_cast<int>(background.position.y), 
                                background.width, 
                                background.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), background.texture, NULL, &backgroundRect) != 0) {
        spdlog::error(u8"backgroundRect called SDL_RenderCopy failed");
    }

    // 渲染玩家
    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, 
                            player.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), player.texture, NULL, &playerRect) != 0) {
        spdlog::error(u8"playerRect called SDL_RenderCopy failed");
    }
    // 渲染玩家子弹
    renderPlayerProjectiles();
}

void SceneMain::Clean() { 
    spdlog::info(u8"Entering SceneMain::Clean()......");


    // 删除背景纹理
    if (background.texture != nullptr) {
        SDL_DestroyTexture(background.texture);
        spdlog::info(u8"[Clean] Background texture destroyed");
    }
    // 删除玩家纹理
    if (player.texture != nullptr) {
        SDL_DestroyTexture(player.texture);
        spdlog::info(u8"[Clean] Player texture destroyed");
    }

    // 删除玩家子弹
    spdlog::info(u8"[Clean] Cleanning projectilesPlayer......");
    for (auto &projectile : projectilesPlayer) {
        if (projectile != nullptr) delete projectile;
    }
    projectilesPlayer.clear();
    spdlog::info(u8"[Clean] Cleaned projectilesPlayer");
    
    // 删除玩家子弹模板
    if (projectilePlayerTemplate.texture != nullptr) {
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
        spdlog::info(u8"[Clean] Cleaned projectilePlayerTemplate texture"); 
    }
}

void SceneMain::keyboardControl(float deltaTime) {
    auto keyboardState = SDL_GetKeyboardState(NULL);
    // 控制玩家移动
    if (keyboardState[SDL_SCANCODE_W]) {
        if (player.position.y > - player.edgeUP * player.zoom + player.deviation)
            player.position.y -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        /**
         * 不明的BUG
         * 不知到为什么，玩家的位置会超过边界
         */
        if (player.position.y < gameInstance.getWindowHeight() - 
                                player.height + player.edgeDown * player.zoom - 
                                player.deviation)
            player.position.y += deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        if (player.position.x > - player.edgeLeft * player.zoom - player.deviation)
            player.position.x -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        if (player.position.x < gameInstance.getWindowWidth() - 
                                player.width + (player.edgeRight * player.zoom) - 
                                player.deviation * player.deviationZoom)
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

void SceneMain::shootPlayer() {
    // 创建新子弹
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    // 定位在飞机顶部中央
    projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;
    projectile->position.y = player.position.y;
    // 添加到活动子弹列表
    projectilesPlayer.push_back(projectile);
}

void SceneMain::updatePlayerProjectiles(float deltaTime)
{
    int margin = 32;
    for (auto it = projectilesPlayer.begin(); it != projectilesPlayer.end();) {
        auto projectile = *it;
        // 更新子弹位置
        projectile->position.y -= projectile->speed * deltaTime;
        // 检查子弹是否超出屏幕
        if (projectile->position.y + margin < 0) {
            delete projectile;
            it = projectilesPlayer.erase(it);
        } else { ++it; }
    }
}

void SceneMain::renderPlayerProjectiles()
{
    for (auto projectile : projectilesPlayer) {
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width, projectile->height };
        if (SDL_RenderCopy(gameInstance.getRenderer(), projectile->texture, NULL, &projectileRect) != 0) {
            spdlog::error(u8"projectilesPlayer called SDL_RenderCopy failed");
        }
    }
}
