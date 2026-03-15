#include "SceneMain.h"
#include "Game.h"


// 引入 gameInstance
SceneMain::SceneMain() : gameInstance(Game::getInstance()) {
    spdlog::info(u8"Entering SceneMain::SceneMain()");
}

SceneMain::~SceneMain() { 
    spdlog::info(u8"Entering SceneMain::~SceneMain()");
}

void SceneMain::Initialize() {
    spdlog::info(u8"Entering SceneMain::Initialize()");


    // 初始化背景
    spdlog::info(u8"Initializing background texture");
    background.texture = IMG_LoadTexture(gameInstance.getRenderer(), u8"assets/Backgrounds/orig.png");
    if (background.texture == nullptr) {
              spdlog::error(u8"Failed to load background texture: {}", SDL_GetError());
    } else { 
        spdlog::info(u8"background.texture loaded successfully");
        spdlog::info(u8"Initializing SDL_QueryTexture");
        SDL_QueryTexture(background.texture, NULL, NULL, &background.width, &background.height);
        spdlog::info(u8"SDL_QueryTexture initialized successfully");
    }
    // 设置玩家缩放比例 设置默认玩家位置
    background.width *= background.zoom;
    background.height *= background.zoom;
    background.position.x = 0;
    background.position.y = 0;

    // 初始化玩家
    spdlog::info(u8"Initializing player.texture");
    player.texture = IMG_LoadTexture(gameInstance.getRenderer(), u8"assets/Foozle_MainShip/Main Ship - Bases/Main Ship - Base - Full health.png");
    if (player.texture == nullptr) {
        spdlog::error(u8"Failed to load player texture: {}", SDL_GetError());
    } else { 
        spdlog::info(u8"Player.texture loaded successfully");
        spdlog::info(u8"Initializing SDL_QueryTexture");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
        spdlog::info(u8"SDL_QueryTexture initialized successfully");
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
}

void SceneMain::Render() {
    // 渲染背景
    SDL_Rect backgroundRect = { static_cast<int>(background.position.x), 
                                static_cast<int>(background.position.y), 
                                background.width, 
                                background.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), background.texture, NULL, &backgroundRect) != 0) {
        spdlog::error(u8"Called SDL_RenderCopy failed");
    }

    // 渲染玩家
    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, 
                            player.height };
    if (SDL_RenderCopy(gameInstance.getRenderer(), player.texture, NULL, &playerRect) != 0) {
        spdlog::error(u8"Called SDL_RenderCopy failed");
    }

}

void SceneMain::Clean() { 
    spdlog::info(u8"Entering SceneMain::Clean()");
    // 删除背景纹理
    if (background.texture != nullptr) {
        SDL_DestroyTexture(background.texture);
        spdlog::info(u8"Background texture destroyed");
    }
    // 删除玩家纹理
    if (player.texture != nullptr) {
        SDL_DestroyTexture(player.texture);
        spdlog::info(u8"Player texture destroyed");
    }
}

void SceneMain::keyboardControl(float deltaTime) {
    auto keyboardState = SDL_GetKeyboardState(NULL);
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
}
